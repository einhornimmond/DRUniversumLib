#include "UniversumLib/lib/Saveable.h"
#include "UniversumLib/task/Saveable.h"
#include "UniversumLib/task/gpu/Saveable.h"
#include "UniversumLib/exception/Task.h"

using namespace std::chrono_literals;

namespace UniLib {
	namespace lib {
		Saveable::~Saveable()
		{
			// can only deconstruct, after storage task is finished or deleted together with scheduler
			while (!mStorageTask.expired()) {
				std::this_thread::sleep_for(100ms);
			}
		}

		void Saveable::asyncSave(std::shared_ptr<DRCommand> finishCommand, bool downloadFromGpu/* = false*/)
		{
			if (!mStorageTask.expired() && mStorageTask.use_count()) {
				throw exception::TaskOrderException("a save task is already running");
			}
			DRTaskPtr task;
			if (downloadFromGpu) {
				DRTaskPtr task = std::make_shared<task::gpu::Saveable>(this);
			}
			else {
				task = std::make_shared<task::Saveable>(this);
			}
			task->setFinishCommand(finishCommand);
			task->scheduleTask(task);
			mStorageTask = task;
		}
	}
}