#ifndef __UNIVERSUM_LIB_TASK_GPU_LOADABLE_H
#define __UNIVERSUM_LIB_TASK_GPU_LOADABLE_H

#include "Task.h"

namespace UniLib {
	namespace lib {
		class Loadable;
	}
	namespace task {
		namespace gpu {
			/*
			* @author einhornimmond
			* @date 05.05.2024
			* @brief loadable cpu and storage task
			*/
			class Loadable : public Task
			{
			public:
				Loadable(lib::Loadable* parent)
					: Task(GPUTaskSpeedType::LOAD), mParent(parent) {}
				virtual ~Loadable();
				virtual DRReturn run();
				virtual const char* getResourceType() const { return "task::gpu::Loadable"; };
			protected:
				lib::Loadable* mParent;
			};
		}
	}
}

#endif //__UNIVERSUM_LIB_TASK_GPU_LOADABLE_H