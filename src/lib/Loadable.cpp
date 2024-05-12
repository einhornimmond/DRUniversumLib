#include "UniversumLib/lib/Loadable.h"
#include "UniversumLib/task/Loadable.h"
#include "UniversumLib/task/gpu/Loadable.h"
#include "UniversumLib/exception/Task.h"
#include "UniversumLib/exception/Loadable.h"
#include "UniversumLib/UniversumLib.h"

#include "DRCore2/DRCore2Main.h"

#include "magic_enum/magic_enum.hpp"

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

		void Loadable::asyncLoad(LoadingStateType target, std::shared_ptr<DRCommand> finishCallback)
		{
			if (!mRunningLoadingTask.expired() && mRunningLoadingTask.use_count()) {
				throw exception::TaskOrderException("a loading task is already running");
			}
			auto currentState = detectLoadingState();
			if (target == currentState || target < currentState) {
				DRLog.writeToLog("loading state: %s", magic_enum::enum_name(target).data());
				LOG_WARNING("try to load state already reached");
				return;
			}

			DRTaskPtr task;
			if (LoadingStateType::STORAGE_DATA_READY == target) {
				task = std::make_shared<task::Loadable>(g_StorageScheduler, this, target);
			} else if (LoadingStateType::CPU_DATA_READY == target) {
				task = std::make_shared<task::Loadable>(g_MainScheduler, this, target);
			} else if (LoadingStateType::GPU_DATA_READY == target) {
				task = std::make_shared<task::gpu::Loadable>(this);
			}
			else {
				throw exception::LoadableInvalidLoadOrder("unhandled target", currentState, target);
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