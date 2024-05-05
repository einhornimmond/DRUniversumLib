/*/*************************************************************************
*                                                                         *
* UniversumLib, collection of classes for generating and go through a     *
* whole universe. It is for my Gameproject Spacecraft					   *
* Copyright (C) 2014, 2015, 2016, 2017 Dario Rekowski.					   *
* Email: dario.rekowski@gmx.de   Web: www.spacecrafting.de                *
*                                                                         *
* This program is free software: you can redistribute it and/or modify    *
* it under the terms of the GNU General Public License as published by    *
* the Free Software Foundation, either version 3 of the License, or       *
* any later version.													   *
*																		   *
* This program is distributed in the hope that it will be useful,	       *
* but WITHOUT ANY WARRANTY; without even the implied warranty of	       *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	       *
* GNU General Public License for more details.							   *
*																		   *
* You should have received a copy of the GNU General Public License	   *
* along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
*                                                                         *
***************************************************************************/

/*!
 * 
 * \author: Dario Rekowski
 *
 * \date: 17.10.2015
 * 
 * \desc: GPU Scheduler control all gpu processing, inclusive the main game loop (GPU part)
 *        Singleton because opengl (interface) is single threaded, only with vulkan multi threaded graphics is possible
 *
 */

#ifndef __DR_UNIVERSUM_LIB_CONTROLLER_GPU_SCHEDULER_H
#define __DR_UNIVERSUM_LIB_CONTROLLER_GPU_SCHEDULER_H

#include "UniversumLib/UniversumLib.h"
#include "Task.h"
#include "UniversumLib/type/GPUSchedulerCommandType.h"

#include "DRCore2/Threading/DRThread.h"
#include "DRCore2/Threading/DRTask.h"

#include "magic_enum/magic_enum.hpp"

#include <memory>
#include <mutex>

namespace UniLib {
	namespace task {
		namespace gpu {

#define GPU_RENDER_LOOP_SAVED_FRAME_DURATION_COUNT 20

			/*
			* Interface for GPU Render Calls, it is a command instead of a task for repeating work
			* things which needed be called every frame over a long period of time
			*/
			class UNIVERSUMLIB_EXPORT IGPURenderCall
			{
			public:
				virtual DRReturn render(float timeSinceLastFrame) = 0;
				// if render return not DR_OK, Call will be removed from List and kicked will be called
				virtual void kicked() = 0;
				// will be called if render call need to much time
				// \param percent used up percent time of render main loop
				virtual void youNeedToLong(float percent) = 0;

				virtual const char* getName() const { return ""; }
			};

			class UNIVERSUMLIB_EXPORT Scheduler : protected DRThread {
			public:
				static Scheduler* const getInstance();
				static const int GPUTaskTargetTimes[];

				void registerGPURenderCommand(IGPURenderCall* renderCall, GPUSchedulerCommandType type);
				void unregisterGPURenderCommand(IGPURenderCall* renderCall, GPUSchedulerCommandType type);

				void addTask(DRTaskPtr task, GPUTaskSpeedType speed = GPUTaskSpeedType::SLOW);

				void startThread(const char* name = "UniGPUSch");
				void stopThread();

				// call frame buffer activities, call main gpu game loop, variable frame rate
				int ThreadFunction();
				// main render function, called from thread or from game
				DRReturn updateEveryRendering();

				// update GPU task from one task Speed Type
				void runTasks(GPUTaskSpeedType taskSpeed);

				inline float getSecondsSinceLastFrame() const { return mSecondsSinceLastFrame; }

				// debugging/profiling
#ifdef DEBUG
				inline size_t getGPUTaskCount(GPUTaskSpeedType taskSpeed) { return mTasks[magic_enum::enum_integer(taskSpeed)].size(); }
				inline size_t getGPURenderCommandCount(GPUSchedulerCommandType type) { return mRenderCommands[magic_enum::enum_integer(type)].size(); }
#endif 
			protected:
				Scheduler();
				virtual ~Scheduler();

				std::mutex mWorkMutex;
				std::list<IGPURenderCall*> mRenderCommands[magic_enum::enum_integer(GPUSchedulerCommandType::ENTRY_COUNT)];
				std::queue<DRTaskPtr>	 mTasks[magic_enum::enum_integer(GPUTaskSpeedType::ENTRY_COUNT)];
				DRProfiler  mLastUpdateTimePoint;
				double mLastFrameDurations[GPU_RENDER_LOOP_SAVED_FRAME_DURATION_COUNT];
				u8    mLastFrameDurationCursor;
				std::atomic<double> mSecondsSinceLastFrame;

			private:
				static Scheduler* mpInstanz;
			};
		}
	}
}


#endif //__DR_UNIVERSUM_LIB_CONTROLLER_GPU_SCHEDULER_H