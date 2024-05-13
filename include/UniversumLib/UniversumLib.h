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

#ifndef __DR_UNIVERSUM_LIB_MAIN_H__
#define __DR_UNIVERSUM_LIB_MAIN_H__

#ifdef _WIN32
#include <windows.h>
#include "Winbase.h"
#else
#include <dlfcn.h>
#endif //_WIN32

#include "UniversumLib/export.h"

#include "DRCore2/DRTypes.h"
#include "DRCore2/Threading/DRCPUScheduler.h"

#include "rapidjson/document.h"

#include <cassert>
#include <sstream>

namespace UniLib {
	namespace controller {
		class BindToRenderer;
		class CPUSheduler;
	};
	UNIVERSUMLIB_EXPORT extern controller::BindToRenderer* g_RenderBinder;
	// 
	UNIVERSUMLIB_EXPORT extern DRCPUScheduler* g_StorageScheduler;
	UNIVERSUMLIB_EXPORT extern DRCPUScheduler* g_MainScheduler;
};

// define OpenGL Types and defines if we haven't openGL
#ifndef GLenum 
typedef unsigned int GLenum;
#endif
#ifndef GLuint
typedef unsigned int GLuint;
#endif
#ifndef GL_RGBA
#define GL_RGBA 0x1908
#endif 
#ifndef GL_RGB
#define GL_RGB 0x1907
#endif
#ifndef GL_COLOR_INDEX
#define GL_COLOR_INDEX 0x1900
#endif


// engine functions
namespace UniLib {	
	// TODO: replace enums with typed enum classes	

	//! \brief 
	//! \param cpuWorkerCount worker count of main scheduler, should be cpu thread count
	//! \param numberParallelStorageOperations count of storage operations (read and write) at the same time
	//!        1 recommended by mechanical hard disks, else more possible    
	UNIVERSUMLIB_EXPORT DRReturn init(int cpuWorkerCount, int numberParallelStorageOperations = 1);
	UNIVERSUMLIB_EXPORT void exit();

	UNIVERSUMLIB_EXPORT void setBindToRenderer(controller::BindToRenderer* bindToRender);
}


#endif //__DR_UNIVERSUM_LIB_MAIN_H__