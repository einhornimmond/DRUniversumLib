#ifndef __UNIVERSUM_LIB_TASK_SAVEABLE_H
#define __UNIVERSUM_LIB_TASK_SAVEABLE_H

#include "UniversumLib/UniversumLib.h"
#include "DRCore2/Threading/DRCPUTask.h"

namespace UniLib {
	namespace lib {
		class Saveable;
	}
	namespace task {
		/*
		* @author einhornimmond
		* @date 05.05.2024
		* @brief task for saving saveables
		*/
		class Saveable : public DRCPUTask
		{
		public:
			Saveable(lib::Saveable* parent)
				: DRCPUTask(g_StorageScheduler), mParent(parent) {}
			virtual ~Saveable();
			virtual DRReturn run();
			virtual const char* getResourceType() const { return "task::Saveable"; };
		protected:
			lib::Saveable* mParent;
		};
	}
}

#endif //__UNIVERSUM_LIB_TASK_SAVEABLE_H