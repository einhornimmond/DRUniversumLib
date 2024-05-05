#include "UniversumLib/lib/Loadable.h"
#include "UniversumLib/task/Loadable.h"
#include "UniversumLib/task/gpu/Loadable.h"
#include "UniversumLib/exception/Task.h"

#include "DRCore2/DRCore2Main.h"

using namespace std::chrono_literals;

namespace UniLib {
	namespace lib {

		Loadable::~Loadable() 
		{
			// can only deconstruct, after loading task is finished or deleted together with scheduler
			while (!mRunningLoadingTask.expired()) {
				std::this_thread::sleep_for(100ms);
			}
		}

		void Loadable::asyncLoad(LoadingStateType target, DRCPUScheduler* loadingScheduler, std::shared_ptr<DRCommand> finishCallback)
		{
			if (!mRunningLoadingTask.expired() && mRunningLoadingTask.use_count()) {
				throw exception::TaskOrderException("a loading task is already running");
			}
			DRTaskPtr task;
			switch (target) {
			case LoadingStateType::STORAGE_DATA_READY: 
			case LoadingStateType::CPU_DATA_READY:
				task = std::make_shared<task::Loadable>(loadingScheduler, this, target);
				break;
			case LoadingStateType::GPU_DATA_READY: 
				task = std::make_shared<task::gpu::Loadable>(this);
				break;
			}
			task->setFinishCommand(finishCallback);
			task->scheduleTask(task);
			mRunningLoadingTask = task;
		}

		void Loadable::updateLoadingState()
		{
			auto state = detectLoadingState();
			mLoadingState = state;
		}
	}
}