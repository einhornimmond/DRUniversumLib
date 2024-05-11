#ifndef __UNIVERSUM_LIB_TASK_LOADABLE_H
#define __UNIVERSUM_LIB_TASK_LOADABLE_H

#include "UniversumLib/type/LoadingStateType.h"
#include "DRCore2/Threading/DRCPUTask.h"
#include "DRCore2/Threading/DRCPUScheduler.h"

namespace UniLib {
	namespace lib {
		class Loadable;
	}
	namespace task {
		/*
		* @author einhornimmond
		* @date 05.05.2024
		* @brief loadable cpu and storage task
		*/
		class Loadable : public DRCPUTask
		{
		public:
			Loadable(DRCPUScheduler* cpuScheduler, lib::Loadable* parent, LoadingStateType targetLoadingState)
				: DRCPUTask(cpuScheduler), mParent(parent), mTargetLoadingState(targetLoadingState) {}
			virtual ~Loadable();
			virtual DRReturn run();
			virtual const char* getResourceType() const { return "task::Loadable"; };
			virtual bool isReady();
		protected:
			LoadingStateType mTargetLoadingState;
			lib::Loadable* mParent;
		};
	}
}

#endif //__UNIVERSUM_LIB_TASK_LOADABLE_H