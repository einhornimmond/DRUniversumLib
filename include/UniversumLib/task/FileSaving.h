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
* \date: 30.04.17
*
* \desc: One generic Task for save one or more files to harddisk, using the harddisk scheduler
*/

#ifndef __DR_UNIVERSUM_LIB_CONTROLLER_FILE_SAVING_TASK_H__
#define __DR_UNIVERSUM_LIB_CONTROLLER_FILE_SAVING_TASK_H__

#include "UniversumLib/export.h"

#include "DRCore2/Threading/DRCPUTask.h"
#include "DRCore2/Foundation/DRVirtualFile.h"

namespace UniLib {
	namespace task {
		class CPUSheduler;
		class UNIVERSUMLIB_EXPORT FileSaving : public DRCPUTask
		{
		public:
			FileSaving(const char* fileName, DRVirtualFile* data, bool freeMemory = true);
			virtual ~FileSaving();

			virtual const char* getResourceType() const { return "FileSavingTask"; };

			virtual DRReturn run();
		protected:
			// input data
			std::string				 mFileName;
			DRVirtualFile*			 mData;
			bool					 mFreeMemory;
		};
	}
}

#endif //__DR_UNIVERSUM_LIB_CONTROLLER_FILE_SAVING_TASK_H__