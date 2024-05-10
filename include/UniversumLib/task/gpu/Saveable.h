#ifndef __UNIVERSUM_LIB_TASK_GPU_SAVEABLE_H
#define __UNIVERSUM_LIB_TASK_GPU_SAVEABLE_H

#include "Task.h"

namespace UniLib {
	namespace lib {
		class Saveable;
	}
	namespace task {
		namespace gpu {
			/*
			* @author einhornimmond
			* @date 05.05.2024
			* @brief saveable, load data from gpu into memory
			*/
			class Saveable : public Task
			{
			public:
				Saveable(lib::Saveable* parent)
					: Task(GPUTaskSpeedType::LOAD), mParent(parent) {}
				virtual ~Saveable();
				virtual DRReturn run();
				virtual const char* getResourceType() const { return "task::gpu::Saveable"; };
			protected:
				lib::Saveable* mParent;
			};
		}
	}
}

#endif //__UNIVERSUM_LIB_TASK_GPU_Saveable_H