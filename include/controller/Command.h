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
 * \author Dario Rekowski
 * 
 * \date 18.03.15
 * 
 * \desc Callback Commands for communication callback, event system
 */

#ifndef __UNIVERSUM_LIB_CONTROLLER_CALLBACKS_H
#define __UNIVERSUM_LIB_CONTROLLER_CALLBACKS_H

#include "UniversumLib.h"

namespace UniLib {
	namespace controller {
		class Task;

		class UNIVERSUM_LIB_API Command 
        {
        public:
            virtual DRReturn taskFinished(Task* task) = 0;
                
        };
    }
}

#endif //__UNIVERSUM_LIB_CONTROLLER_CALLBACKS_H