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
 * \date 11.12.2015
 * 
 * \desc contain every active block type which can be rendered with instancing
 */

#ifndef _DR_UNIVERSUM_LIB_CONTROLLER_INSTANCING_BLOCK_MANAGER_H_
#define _DR_UNIVERSUM_LIB_CONTROLLER_INSTANCING_BLOCK_MANAGER_H_

#include "UniversumLib/view/block/GeometrieBlock.h"

#include <map>

namespace UniLib {
	namespace manager {
		class UNIVERSUMLIB_EXPORT InstancingBlocks
		{
		public:
			// return the one and one instance (create if not exist)
			static InstancingBlocks* getInstance();

			virtual std::shared_ptr<view::block::GeometrieBlock> findGeometrieBlock(HASH id);
			void clearEmptyGeometrieBlocks();
		protected:
			InstancingBlocks();
			virtual ~InstancingBlocks();

			std::map<HASH, std::shared_ptr<view::block::GeometrieBlock>> mGeometrieBlocks;
		};
	}
}

#endif //_DR_UNIVERSUM_LIB_CONTROLLER_INSTANCING_BLOCK_MANAGER_H_