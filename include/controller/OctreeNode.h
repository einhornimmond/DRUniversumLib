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
 * \date: 27.12.15
 *
 * \desc: A Node in a Octree
 */

#ifndef __DR_UNIVERSUM_LIB_CONTROLLER_OCTREE_NODE_H__
#define __DR_UNIVERSUM_LIB_CONTROLLER_OCTREE_NODE_H__


#include "model/Sektor.h"

namespace UniLib {
	namespace model {
		class SektorID;
	}
    namespace controller {
		class OctreeNode;

		class UNIVERSUM_LIB_API OctreeNode : public model::Sektor
		{
		public:
			OctreeNode(model::SektorID* id, model::Node* parent = NULL);
			virtual ~OctreeNode();

			// update 
			virtual DRReturn move(float timeSinceLastFrame);

			__inline__ model::Node* operator[] (DRVector3i index) {
				assert(index.x == 0 || index.x == 1);
				assert(index.y == 0 || index.y == 1);
				assert(index.z == 0 || index.z == 1);
				return mChilds[index.z*4+index.y*2+index.x];
			}
			__inline__ model::Node* operator[] (u8 index) {
				assert(index >= 0 && index < 8);
				return mChilds[index];
			}

			// get name of sektor type
			virtual const char* getSektorType() { return "OctreeNode"; };			

		protected:
			model::Node* mChilds[8];
		};
	}
}

#endif //__DR_UNIVERSUM_LIB_CONTROLLER_OCTREE_NODE_H__