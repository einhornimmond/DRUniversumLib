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


#ifndef __UNI_LIB_MODEL_H
#define __UNI_LIB_MODEL_H

#include "UniversumLib/export.h"

/*!
 *
 * \author: Dario Rekowski
 *
 * \date: 23.01.2016
 *
 * \brief: base class for scene nodes, contains parent and child pointer
 *
 */
namespace UniLib {
	namespace model {

		class UNIVERSUMLIB_EXPORT Model
		{
		public:
			Model() {}
			virtual ~Model() {};

			
		protected:
		};

	}
}

#endif //__UNI_LIB_MODEL_H