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

#ifndef __UNIVERSUM_LIB_CONTROLLER_BLOCK_SECTOR_TREE_H
#define __UNIVERSUM_LIB_CONTROLLER_BLOCK_SECTOR_TREE_H
/*!
* \author Dario Rekowski
*
* \date 02.03.16
*
* \desc Node controlling OctreeNode with BlockSector Leafs
*
*/

#include "OctreeNode.h"

#include <memory>

namespace UniLib {
	namespace model {
		class SectorID;
		class BlockSector;

		namespace block {
			class Block;
			typedef std::shared_ptr<Block> BlockPtr;
		}
	}
	namespace controller {
		class UNIVERSUMLIB_EXPORT BlockSectorTree : public OctreeNode
		{
		public:
			BlockSectorTree(model::SectorID* id, model::Node* parent);
			virtual ~BlockSectorTree();

			virtual DRReturn move(float timeSinceLastFrame);

			virtual const char* getSectorType() { return "BlockSectorTree"; };

			// \brief add block
			// \param block block to add
			// \param id of block sektor
			// \param pos position inside BlockSector
			DRReturn addBlock(model::block::BlockPtr block, std::queue<u8> path, DRVector3i pos);
		protected:
		};

	}
}


#endif //__UNIVERSUM_LIB_CONTROLLER_BLOCK_SECTOR_TREE_H