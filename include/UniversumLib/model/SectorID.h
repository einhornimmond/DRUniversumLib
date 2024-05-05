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

/**
 * \author Dario Rekowski
 * 
 * \date 19.03.15
 * 
 * \desc SectorID, a unique ID for every sektor, contains complete sektor path
 */

#ifndef __DR_UNIVERSUM_LIB_MODEL_SEKTOR_ID_H__ 
#define __DR_UNIVERSUM_LIB_MODEL_SEKTOR_ID_H__

#include "UniversumLib/export.h"
#include "UniversumLib/type/SectorIdType.h"

#include "DRCore2/DRTypes.h"

namespace UniLib {
    namespace model {
		
        class UNIVERSUMLIB_EXPORT SectorID
        {
        public:
			SectorID(u8 id, SectorIdType type, SectorID* parent = nullptr);
			SectorID(u16 id, SectorIdType type, SectorID* parent = nullptr);
			SectorID(u32 id, SectorIdType type, SectorID* parent = nullptr);
			SectorID(u64 id, SectorIdType type, SectorID* parent = nullptr);
			SectorID(u8* id, u8 arraySize, SectorIdType type, SectorID* parent = nullptr);
			
			virtual ~SectorID();

			// fill buffer with serialized id
			DRReturn serialize(u8* buffer);
			int getSeralizedSize();

			// create Sector ID Object tree from id
			static SectorID* deserialize(u8* id, u8 arraySize, SectorID* parent = NULL);

			inline void setParent(SectorID* parent) { mParent = parent; }

        protected:
			u8* mID;
			u8 mArraySize;
			u8 mType;
			SectorID* mParent;
        };
    }
}

#endif //__DR_UNIVERSUM_LIB_MODEL_SEKTOR_ID_H__