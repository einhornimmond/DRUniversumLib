#include "UniversumLib/task/FileLoading.h"
#include "UniversumLib/UniversumLib.h"

namespace UniLib {
	namespace task {
		FileLoading::FileLoading(FileLoadingReciver* reciver, const char* fileName)
			: DRCPUTask(g_StorageScheduler), mFinishReciver(reciver), mFinished(false)
		{
			assert(reciver != NULL);
			mFileNames.push_back(fileName);
			mFilesInMemory = new DRVirtualFile*;
#ifdef DEBUG
			setName(fileName);
#endif
		}

		FileLoading::FileLoading(FileLoadingReciver* reciver, std::vector<std::string> fileNames)
			: DRCPUTask(g_StorageScheduler), mFinishReciver(reciver), mFileNames(fileNames), mFinished(false)
		{
#ifdef DEBUG
			setName(fileNames[0].data());
#endif
			assert(reciver != NULL);
			mFilesInMemory = new DRVirtualFile*[mFileNames.size()];
			memset(mFilesInMemory, 0, sizeof(DRVirtualFile*)*mFileNames.size());
		}
		FileLoading::~FileLoading()
		{
			if (mFileNames.size() > 1) {
				DR_SAVE_DELETE_ARRAY(mFilesInMemory);
			}
			else { 
				DR_SAVE_DELETE(mFilesInMemory);
			}
			mFileNames.clear();
		}

		DRReturn FileLoading::run()
		{
			for (u16 i = 0; i < mFileNames.size(); i++) {
				DRFile file(mFileNames[i].data(), "rb");
				if (file.isOpen()) {
					char start[11]; memset(start, 0, 11);
					if (file.getSize() > 10) {
						file.read(start, 1, 10);
						file.close();
						if (strcmp(start, VIRTUAL_FILE_HEAD) == 0) {
							mFilesInMemory[i] = new DRVirtualCustomFile();
							mFilesInMemory[i]->readFromFile(mFileNames[i].data());
							continue;
						} 
					} else {
						file.close();
					}
					mFilesInMemory[i] = new DRVirtualBinaryFile();
					
					mFilesInMemory[i]->readFromFile(mFileNames[i].data());
				}
				//mData[i] = (void*)malloc()
			}
			bool result = false;
			
			if (mFileNames.size() == 1) {
				result = mFinishReciver->getFileFromMemory(*mFilesInMemory);
			}
			else {
				result = mFinishReciver->getFileFromMemory(mFilesInMemory, mFileNames.size());
			}
			if (result != true) {
				for (u16 i = 0; i < mFileNames.size(); i++) {
					if (!mFilesInMemory[i]) continue;
					mFilesInMemory[i] = NULL;
				}
			}
			{
				auto lock = getUniqueLock();
				mFinished = true;
			}
			mFinishReciver->finishFileLoadingTask();
			
			return DR_OK;
		}

		bool FileLoading::isTaskFinished()
		{
			auto lock = getUniqueLock();
			return mFinished;
		}
	}

	
}