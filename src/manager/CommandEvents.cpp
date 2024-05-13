#include "Universumlib/manager/CommandEvents.h"
#include "DRCore2/Foundation/DRHash.h"
#include "DRCore2/DRCore2Main.h"

namespace UniLib {
	namespace manager {
		CommandEvents::CommandEvents()
		{

		}

		CommandEvents::~CommandEvents()
		{

		}

		DRReturn CommandEvents::init()
		{
			return DR_OK;
		}

		void CommandEvents::exit()
		{
			UNIQUE_LOCK;
			for (auto commandList : mCommandsMap) {
				commandList.second.clear();
			}
			mCommandsMap.clear();
		}

		DRReturn CommandEvents::addCommandForEvent(const char* eventName, std::shared_ptr<DRCommand> command)
		{
			
#ifdef DEBUG
			UNIQUE_LOCK;
			// doubletten check
			HASH hash = DRMakeStringHash(eventName);
			auto it = mHashNameMap.find(hash);
			if(it != mHashNameMap.end()) {
				assert(it->second == std::string(eventName));
			} else {
				mHashNameMap.insert({ hash, std::string(eventName) });
			}
#endif
			return addCommandForEvent(DRMakeStringHash(eventName), command);
		}
		DRReturn CommandEvents::addCommandForEvent(HASH eventHash, std::shared_ptr<DRCommand> command)
		{
			UNIQUE_LOCK;
			auto it = mCommandsMap.find(eventHash);
			if(it == mCommandsMap.end()) {
				mCommandsMap.insert({ eventHash, CommandList() });
				it = mCommandsMap.find(eventHash);
			}
			if(it != mCommandsMap.end()) {
				it->second.push_back(command);
			} else {
				LOG_ERROR("error adding command to map", DR_ERROR);
			}
			return DR_OK;
		}
		void CommandEvents::removeCommandForEvent(const char* eventName, std::shared_ptr<DRCommand> command)
		{
			removeCommandForEvent(DRMakeStringHash(eventName), command);
		}
		void CommandEvents::removeCommandForEvent(HASH eventHash, std::shared_ptr<DRCommand> command)
		{
			UNIQUE_LOCK;
			auto it = mCommandsMap.find(eventHash);
			if(it != mCommandsMap.end()) {
				for(CommandList::iterator commandIt = it->second.begin(); commandIt != it->second.end(); commandIt++) {
					if(*commandIt == command) {
						it->second.erase(commandIt);
						return;
					}
				}
			}
		}

		void CommandEvents::triggerEvent(const char* name, DRTask* task)
		{
			triggerEvent(DRMakeStringHash(name), task);
		}
		void CommandEvents::triggerEvent(HASH eventHash, DRTask* task)
		{
			UNIQUE_LOCK;
			auto it = mCommandsMap.find(eventHash);
			if(it != mCommandsMap.end()) {
				for (auto command : it->second) {
					command->taskFinished(task);
				}
			}
		}
	}
}