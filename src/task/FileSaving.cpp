#include "UniversumLib/task/FileSaving.h"
#include "UniversumLib/UniversumLib.h"

#include "DRCore2/DRCore2Main.h"

namespace UniLib {
	namespace task {
		FileSaving::FileSaving(const char* fileName, DRVirtualFile* data, bool freeMemory /* = true */)
			: DRCPUTask(g_StorageScheduler), mFileName(fileName), mData(data), mFreeMemory(freeMemory)
		{
#ifdef DEBUG
			setName(fileName);
#endif
		}

		FileSaving::~FileSaving()
		{
			if (mFreeMemory) {
				DR_SAVE_DELETE(mData);
			}
		}

		DRReturn FileSaving::run()
		{
			if (mData->saveToFile(mFileName.data())) {
				LOG_ERROR("error saving data to file", DR_ERROR);
			}
			return DR_OK;
		}
	}
}