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

#ifndef __UNIVERSUM_LIB_MANAGER_BASE_GEOMETRIE_MANAGER_H
#define __UNIVERSUM_LIB_MANAGER_BASE_GEOMETRIE_MANAGER_H
/*!
* \author Dario Rekowski
*
* \date 20.03.16
*
* \desc Contains Base Geometries
*
*/

#include "UniversumLib/export.h"
#include "UniversumLib/type/BaseGeometrieType.h"
#include "UniversumLib/task/gpu/Scheduler.h"
#include "UniversumLib/view/Geometrie.h"

#include "DRCore2/Threading/DRCPUTask.h"
#include "DRCore2/Threading/DRCPUScheduler.h"
#include "DRCore2/DRTypes.h"

#include "magic_enum/magic_enum.hpp"

#include <mutex>

namespace UniLib {
	namespace view {
		class Geometrie;
	}
	namespace manager {
		
		class BaseGeometrieLoadingGPUTask;

		class UNIVERSUMLIB_EXPORT BaseGeometries
		{
		public:
			static BaseGeometries* getInstance();

			DRReturn init(DRCPUScheduler* cpuScheduler = NULL);
			void exit();

			//! \brief get pointer to geometrie, create if necessary
			
			view::GeometriePtr getGeometrie(BaseGeometrieType type);
		protected:
			BaseGeometries();
			virtual ~BaseGeometries();

			view::GeometriePtr mGeometrieArray[magic_enum::enum_integer(BaseGeometrieType::ENTRY_COUNT)];
			DRCPUScheduler* mCPUScheduler;
			bool mInitalized;
			std::mutex mMutex;
		};
	}
}

#endif __UNIVERSUM_LIB_MANAGER_BASE_GEOMETRIE_MANAGER_H