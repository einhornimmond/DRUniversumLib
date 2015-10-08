/*/*************************************************************************
 *                                                                         *
 * EngineDLL, Engine for my programs, using SDL and OpenGL		   *
 * Copyright (C) 2012, 2013, 2014 Dario Rekowski.			   *
 * Email: dario.rekowski@gmx.de   Web: www.spacecrafting.de                *
 *                                                                         *
 * This program is free software: you can redistribute it and/or modify    *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation, either version 3 of the License, or       *
 * any later version.							   *
 *									   *
 * This program is distributed in the hope that it will be useful,	   *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of	   *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	   *
 * GNU General Public License for more details.				   *
 *									   *
 * You should have received a copy of the GNU General Public License	   *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
 *                                                                         *
 ***************************************************************************/

/*!
 
 \brief Container Wrapper class for mutex protected container

 \author Dario Rekowski

 \date 08.10.2015
*/

#ifndef __DR_UNIVERSUM_LIB_LIB_MULTITHREAD_CONTAINER_H__
#define __DR_UNIVERSUM_LIB_LIB_MULTITHREAD_CONTAINER_H__

#include "UniversumLib.h"

namespace UniLib {
	namespace lib {
		class UNIVERSUM_LIB_API MultithreadContainer
		{
		public:
			MultithreadContainer();
			virtual ~MultithreadContainer();

			__inline__ void lock() {SDL_LockMutex(mWorkMutex);}
			__inline__ void unlock() {SDL_UnlockMutex(mWorkMutex);}
		protected:
		private:
			SDL_mutex* mWorkMutex;
		};
	}
}

#endif //__DR_UNIVERSUM_LIB_LIB_MULTITHREAD_CONTAINER_H__