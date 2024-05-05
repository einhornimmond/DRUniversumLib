#include "UniversumLib/task/gpu/Task.h"
#include "UniversumLib/task/gpu/Scheduler.h"

namespace UniLib {
	namespace task {
		namespace gpu {
			Task::Task(GPUTaskSpeedType taskSpeed/* = GPU_TASK_FAST*/)
				:DRTask(0), mTaskSpeed(taskSpeed)
			{

			}
			Task::Task(size_t childCount, GPUTaskSpeedType taskSpeed /*= GPU_TASK_FAST*/)
				:DRTask(childCount), mTaskSpeed(taskSpeed)
			{

			}

			Task::~Task()
			{

			}

			void Task::scheduleTask(DRTaskPtr own) {
				Scheduler::getInstance()->addTask(own, mTaskSpeed);
			}
		}
	}
}