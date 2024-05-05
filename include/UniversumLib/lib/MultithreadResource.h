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
 * \date: 06.03.2016
 *
 * \desc: a resource with loading state and working mutex
 *
 *
 */

#ifndef __DR_UNIVERSUM_LIB_LIB_MULTITHREAD_RESOURCE_H
#define __DR_UNIVERSUM_LIB_LIB_MULTITHREAD_RESOURCE_H

#include "UniversumLib/export.h"
#include "UniversumLib/type/LoadingStateType.h"

#include "DRCore2/Foundation/DRIResource.h"
#include "DRCore2/Threading/DRMultithreadContainer.h"

namespace UniLib {
	namespace lib {
		class UNIVERSUMLIB_EXPORT MultithreadResource : public DRIResource, protected DRMultithreadContainer
		{
		public:
			MultithreadResource() : mLoadingState(LoadingStateType::EMPTY) {};
			MultithreadResource(LoadingStateType loadingState) : mLoadingState(loadingState) {}
			virtual ~MultithreadResource() {};

			virtual bool less_than(MultithreadResource& b) { return mLoadingState < b.mLoadingState; }
			
			// check and manipulate loading state
			inline LoadingStateType checkLoadingState() { UNIQUE_LOCK; return mLoadingState; }
			
		protected:
			virtual void setLoadingState(LoadingStateType state) { UNIQUE_LOCK; mLoadingState = state; }
			LoadingStateType mLoadingState;
		};
	}
}

#endif //__DR_UNIVERSUM_LIB_LIB_MULTITHREAD_RESOURCE_H