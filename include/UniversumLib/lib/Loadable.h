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

\brief class for asynchron loading, use cpu, gpu and storage tasks 

\author Dario Rekowski

\date 17.04.2016
*/

#ifndef DR_UNIVERSUM_LIB_LIB_LOADABLE_H
#define DR_UNIVERSUM_LIB_LIB_LOADABLE_H

#include "UniversumLib/export.h"
#include "UniversumLib/type/LoadingStateType.h"

#include "DRCore2/Threading/DRTask.h"
#include "DRCore2/Threading/DRCPUScheduler.h"

#include <atomic>
#include <mutex>

namespace UniLib {
	namespace lib {
		class UNIVERSUMLIB_EXPORT Loadable
		{
		public:
			Loadable() : mLoadingState(LoadingStateType::EMPTY) {};
			Loadable(LoadingStateType loadingState) : mLoadingState(loadingState) {};
			virtual ~Loadable();

			//! \param start task for calling load async
			//! \param target target loading state
			//! \param finishCallback called after finish loading
			void asyncLoad(LoadingStateType target, std::shared_ptr<DRCommand> finishCallback = nullptr);

			LoadingStateType checkLoadingState() const { return mLoadingState; }			
			inline void updateLoadingState() { mLoadingState = detectLoadingState();}
			//! actuall load code
			virtual DRReturn load(LoadingStateType target) = 0;
			//! overload if loading task must wait for other tasks finishing first
			virtual bool isReadyForLoad(LoadingStateType target) { return true; }
		protected:
			//! calculate current loading state based on data
			virtual LoadingStateType detectLoadingState() = 0;
			void setLoadingState(LoadingStateType state) { mLoadingState = state; }
			std::atomic<LoadingStateType> mLoadingState;
			// for checking running loading task
			std::weak_ptr<DRTask> mRunningLoadingTask;
		};
	}
}

#endif // !DR_UNIVERSUM_LIB_LIB_LOADABLE_H
