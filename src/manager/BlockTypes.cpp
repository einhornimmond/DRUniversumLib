#include "UniversumLib/controller/BlockTypeManager.h"
#include "UniversumLib/model/block/MaterialBlock.h"

#include "DRCore2/Utils/DRProfiler.h"

namespace UniLib {
	namespace manager {

		// CPU TASK 
		// parsing block type data
		DRReturn BlockTypeLoadingTask::run()
		{
			return BlockTypeManager::getInstance()->_parsingJsonToBlockTypes(mFileContent);
		}
		// loading files with config data into memory
		DRReturn LoadingJsonFilesIntoMemoryTask::run()
		{
			std::string fileContent = readFileAsString(mFileName);
			DRTaskPtr task(new BlockTypeLoadingTask(mSchedulerForParser, fileContent));
#ifdef DEBUG
			task->setName(mFileName.data());
#endif
			task->scheduleTask(task);	

			return DR_OK;
		}
		// ************************************************************************************************++
		// BLock Material Manager
		// ************************************************************************************************++

		BlockTypeManager::BlockTypeManager() 
			: mLoadingState(LOADING_STATE_EMPTY)
		{

		}

		BlockTypeManager::~BlockTypeManager()
		{
			exit();
		}

		BlockTypeManager* BlockTypeManager::getInstance()
		{
			static BlockTypeManager theOne;
			return &theOne;
		}
		// called from io Thread or directly
		DRReturn BlockTypeManager::init(const std::list<std::string>* fileNames)
		{
			for (std::list<std::string>::const_iterator it = fileNames->begin(); it != fileNames->end(); it++) {
				if (_parsingJsonToBlockTypes(readFileAsString(*it))) {
					LOG_ERROR("error by parsing Json to block types", DR_ERROR);
				}
			}
			return DR_OK;
			
			//return _init();
		}
		DRReturn BlockTypeManager::initAsyn(const std::list<std::string>* fileNames, DRCPUScheduler* scheduler)
		{
			for (std::list<std::string>::const_iterator it = fileNames->begin(); it != fileNames->end(); it++) {
				DRTaskPtr task(new LoadingJsonFilesIntoMemoryTask(*it, scheduler));
				task->scheduleTask(task);
#ifdef DEBUG
				task->setName(it->data());
#endif
			}
			
			
			return DR_OK;
		}
		
	
		//DRReturn _parsingJsonToBlockTypes(const std::string& mFilesContent);
		DRReturn BlockTypeManager::_parsingJsonToBlockTypes(const std::string& mFileContent)
		{			
			DRProfiler startTicks;
			{
				UNIQUE_LOCK;
				mLoadingState = LOADING_STATE_HAS_INFORMATIONS;
			}
			
			Json::Value json = convertStringToJson(mFileContent);
			Json::Value material = json.get("materialTypes", Json::Value());
			if (material.isArray()) {
				for (int i = 0; i < material.size(); i++) {
					Json::Value entry = material[i];
					std::string name = entry.get("name", "noname").asString();
					HASH id = DRMakeStringHash(name.data());
					auto lock = getUniqueLock(__FUNCTION__);
					BlockTypelIter it = mBlockTypes.find(id);
					if (it != mBlockTypes.end()) {
						if (std::string(it->second->getName()) != name) {
							DRLog.writeToLog("Material %s and Material %s have the same hash: %d",
								it->second->getName(), name.data(), id);
							mWorkMutex.unlock();
							LOG_ERROR("hash collision", DR_ERROR);
						}
						else {
							DRLog.writeToLog("material: %s", name.data());
							LOG_WARNING("One material was declared more than once");
						}
					}
					else {
						lock.unlock();
						model::block::MaterialBlock* mat = new model::block::MaterialBlock(name);
						if (mat->initFromJson(entry)) {
							delete mat;
							LOG_ERROR("error by init one material", DR_ERROR);
						}
						mat->setId(id);
						lock.lock();
						mBlockTypes.insert(BlockTypePair(id, mat));
						mLoadingState = LOADING_STATE_PARTLY_LOADED;
					}
					mWorkMutex.unlock();
				}
			}
			else {
				LOG_ERROR("json isn't a array", DR_ERROR);
			}
			{
				UNIQUE_LOCK;
				mLoadingState = LOADING_STATE_PARTLY_LOADED;
			}
			//EngineLog.writeToLog("[BlockTypeManager::_parsingJsonToBlockTypes] running time: %d ms", SDL_GetTicks() - startTicks);
			return DR_OK;
		}

		model::block::BlockType* BlockTypeManager::getBlockType(HASH id)
		{
			mWorkMutex.lock();
			BlockTypelIter it = mBlockTypes.find(id);
			model::block::BlockType* result = NULL;
			if (it != mBlockTypes.end()) {
				result = it->second;
			}
			mWorkMutex.unlock();
			return result;
		}

		void BlockTypeManager::exit()
		{
			mWorkMutex.lock();
			for(BlockTypelIter it = mBlockTypes.begin(); it != mBlockTypes.end(); it++) {
				delete it->second;
			}
			mBlockTypes.clear();
			mWorkMutex.unlock();
		}
	}
}