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


#ifndef __UNI_LIB_MODEL_SMALL_BLOCK_SEKTOR_H
#define __UNI_LIB_MODEL_SMALL_BLOCK_SEKTOR_H

#include "Sector.h"
/*!
 *
 * \author: Dario Rekowski
 *
 * \date: 17.01.2016
 *
 * \brief: class for sector containing blocks
 * index only allowed in range 0-3
 *
 */
namespace UniLib {
	namespace view {
		class BlockSector;
	}
	namespace model {
		namespace block {
			class Block;
			typedef DRResourcePtr<Block> BlockPtr;
		}
		class BlockSector;
		class UNIVERSUM_LIB_API SmallBlockSector : public Sector 
		{
		public:
			SmallBlockSector(view::BlockSector* viewSector);
			virtual ~SmallBlockSector();

			
			inline block::BlockPtr operator[] (DRVector3i index) const
			{
				assert(index.x >= 0 && index.x < 4);
				assert(index.y >= 0 && index.y < 4);
				assert(index.z >= 0 && index.z < 4);
				return (*this)[DRMakeSmallVector3DHash(index)];
			}
			
			inline bool isPlaceFree(DRVector3i index) const {return isPlaceFree(DRMakeSmallVector3DHash(index));}

			// return DR_ERROR if place is already occupied
			DRReturn addBlock(block::BlockPtr block, DRVector3i index);
			block::BlockPtr deleteBlock(DRVector3i index);

			// overrides
			// get name of sektor type
			virtual const char* getSectorType() {return "SmallBlockSector";}
			// calculate current visibility mode for given camera, multiple calls per frame possible
			virtual DRReturn updateVisibility(view::Camera* camera);
			// move/update objects in sektor
			virtual DRReturn move(float timeSinceLastFrame);
			
		protected:

			//bool isPlaceFree(HASH h) const {return mBlocks.find(h) == mBlocks.end();}
			block::BlockPtr operator[] (HASH h) const;

			// bit sets on every place with an solid block (not transparency)
			u8 mGridSolid[3][3]; 
		};


	}
}

#endif //__UNI_LIB_MODEL_SMALL_BLOCK_SEKTOR_H