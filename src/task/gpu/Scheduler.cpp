#include "UniversumLib/task/gpu/Scheduler.h"
#include "UniversumLib/task/gpu/Task.h"

#include "DRCore2/DRCore2Main.h"
#include "DRCore2/Threading/DRCPUSchedulerTasksLog.h"
#include "DRCore2/Utils/DRProfiler.h"

#include "magic_enum/magic_enum_utility.hpp"

#include <chrono>

using namespace std::chrono_literals;

namespace UniLib {
	namespace task {
		namespace gpu {

			Scheduler* Scheduler::mpInstanz = NULL;
			/*
			* time in milliseconds which are allowed for gpu tasks
			* will directly affect frames per seconds, especially lows on slower systemes
			* TODO: make it configurable
			* GPU_TASK_FAST = 0,
			* GPU_TASK_SLOW = 1,
			* GPU_TASK_LOAD = 2,
			*/
			const int Scheduler::GPUTaskTargetTimes[] = { 2, 10, 250 };

			Scheduler::Scheduler()
				: DRThread(nullptr), mLastFrameDurationCursor(0)
			{
				memset(mLastFrameDurations, 16, sizeof(int) * GPU_RENDER_LOOP_SAVED_FRAME_DURATION_COUNT);
			}


			Scheduler::~Scheduler()
			{
				stopThread();
			}

			Scheduler* const Scheduler::getInstance()
			{
				if (!mpInstanz) {
					mpInstanz = new Scheduler;
				}

				return (Scheduler*)mpInstanz;
			}

			void Scheduler::startThread(const char* name /* = "UniGPUSch" */)
			{
				DRThread::setName(name);
				DRThread::init();
				mLastUpdateTimePoint.reset();
			}

			void Scheduler::registerGPURenderCommand(IGPURenderCall* renderCall, GPUSchedulerCommandType type)
			{
				std::unique_lock _lock(mWorkMutex);
				mRenderCommands[magic_enum::enum_integer(type)].push_back(renderCall);
			}
			void Scheduler::unregisterGPURenderCommand(IGPURenderCall* renderCall, GPUSchedulerCommandType type)
			{
				std::unique_lock _lock(mWorkMutex);
				mRenderCommands[magic_enum::enum_integer(type)].remove(renderCall);
			}
			void Scheduler::addTask(DRTaskPtr task, GPUTaskSpeedType speed /*= GPU_TASK_SLOW*/)
			{
				assert(speed < GPUTaskSpeedType::ENTRY_COUNT);
				auto gpuTask = dynamic_cast<Task*>(task.get());
				if (!gpuTask) {
					LOG_ERROR_VOID("isn't gpu task");
				}
				std::unique_lock _lock(mWorkMutex);
				mTasks[magic_enum::enum_integer(speed)].push(task);
			}

			int Scheduler::ThreadFunction()
			{
				while (true) {
					if (isExitCalled()) {
						return 0;
					}
					if (updateEveryRendering()) {
						stopThread();
						LOG_ERROR("error in main game rendering loop", DR_ERROR);
					}
				}
				return 0;
			}

			void Scheduler::runTasks(GPUTaskSpeedType taskSpeed)
			{
				assert(taskSpeed < GPUTaskSpeedType::ENTRY_COUNT);
				auto taskSpeedIndex = magic_enum::enum_integer(taskSpeed);
				u32 reQueueCount = 0;
				DRProfiler timer;

#ifdef PROFILING
				DRCPUSchedulerTasksLog* l = DRCPUSchedulerTasksLog::getInstance();
				std::string runningTasksTable;
#endif
				std::unique_lock _lock(mWorkMutex, std::adopt_lock);
				while (mTasks[taskSpeedIndex].size() - reQueueCount) {
					auto task = mTasks[taskSpeedIndex].front();
					if (!task) continue;
					mTasks[taskSpeedIndex].pop();
					if (task->isReady()) {
#ifdef PROFILING
						l->addTaskLogEntry((u64)task.get(), task->getResourceType(), magic_enum::enum_name(taskSpeed).data(), task->getName());
						runningTasksTable = l->getCurrentlRunningTasksTableString();
#endif
						_lock.unlock();
						task->run();
						_lock.lock();
#ifdef PROFILING
						l->removeTaskLogEntry((u64)task.get());
						DRSpeedLog.writeToLog("%s used on %s by Task: %s of: %s",
							timer.string().data(), magic_enum::enum_name(taskSpeed).data(), task->getResourceType(), task->getName());
#endif
					}
					else {
						mTasks[taskSpeedIndex].push(task);
						reQueueCount++;
					}
					if (timer.millis() > GPUTaskTargetTimes[taskSpeedIndex]) {
#ifdef DEBUG
						DRLog.writeToLogDirect(runningTasksTable);
						runningTasksTable = "";
#endif
						DRLog.writeToLog("<font color='red'>used %s from %s</font>", timer.string().data(), magic_enum::enum_name(taskSpeed).data());
						LOG_WARNING("GPU Task used more then allowed");
						break;
					}
					// only fast Tasks allowed multiple times per frame
					if (taskSpeed != GPUTaskSpeedType::FAST) {
						break;
					}
				}
			}

			DRReturn Scheduler::updateEveryRendering()
			{
				double secondsSinceLastFrame = 0.0;
				double sumFrames = 0;
				// smooth frame time over GPU_RENDER_LOOP_SAVED_FRAME_DURATION_COUNT frames
				for (int i = 0; i < GPU_RENDER_LOOP_SAVED_FRAME_DURATION_COUNT; i++) {
					sumFrames += mLastFrameDurations[i];
				}
				secondsSinceLastFrame = (sumFrames / static_cast<double>(GPU_RENDER_LOOP_SAVED_FRAME_DURATION_COUNT)) / 1000.0;
				mSecondsSinceLastFrame = secondsSinceLastFrame;

				DRProfiler startTicks;

				std::unique_lock _lock(mWorkMutex);
				// run different expensive gpu tasks
				// max 2 ms for fast tasks, one slow and one load task
				runTasks(GPUTaskSpeedType::FAST);
				runTasks(GPUTaskSpeedType::SLOW);
				runTasks(GPUTaskSpeedType::LOAD);

#ifdef PROFILING
				DRCPUSchedulerTasksLog* l = DRCPUSchedulerTasksLog::getInstance();
#endif
				// update render calls
				magic_enum::enum_for_each<GPUSchedulerCommandType>([&](auto val) {
					constexpr GPUSchedulerCommandType commandType = val;
					if (commandType == GPUSchedulerCommandType::ENTRY_COUNT) return;
					auto commandTypeIndex = magic_enum::enum_integer(commandType);
					for (std::list<IGPURenderCall*>::iterator it = mRenderCommands[commandTypeIndex].begin(); it != mRenderCommands[commandTypeIndex].end(); it++) {
						DRProfiler ticks;
#ifdef PROFILING
						l->addTaskLogEntry(1, magic_enum::enum_name(commandType).data(), "GPU Render Call", (*it)->getName());
#endif 
						DRReturn result = (*it)->render(secondsSinceLastFrame);
#ifdef PROFILING
						l->removeTaskLogEntry(1);
#endif
						auto diff = ticks.millis();
						if (result) {
							(*it)->kicked();
							
							it = mRenderCommands[commandTypeIndex].erase(it);
							if (it == mRenderCommands[commandTypeIndex].end()) break;
						}
						else {
							if ((diff > 0.2 && commandType != GPUSchedulerCommandType::RENDERING) ||
								diff > 5.0 && commandType == GPUSchedulerCommandType::RENDERING) {
								(*it)->youNeedToLong(((float)diff) / secondsSinceLastFrame);
							}
						}
					}
				});
				
				// if we have time left, let's run some more slow gpu tasks
				while (startTicks.duration() < 15ms && mTasks[magic_enum::enum_integer(GPUTaskSpeedType::SLOW)].size()) {
					//runSlowGPUTask();
					runTasks(GPUTaskSpeedType::SLOW);
				}
				_lock.unlock();
				// if we have still time left, we wait
				if (startTicks.duration() < 16ms) {
					std::this_thread::sleep_for(15ms - startTicks.duration());
				}

				mLastFrameDurations[mLastFrameDurationCursor++] = mLastUpdateTimePoint.millis();
				if (mLastFrameDurationCursor >= GPU_RENDER_LOOP_SAVED_FRAME_DURATION_COUNT) mLastFrameDurationCursor = 0;
				mLastUpdateTimePoint.reset();
				return DR_OK;
			}

			void Scheduler::stopThread()
			{
				DRThread::exit();
			}
		}
	}
}