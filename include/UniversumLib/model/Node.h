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

#ifndef __UNI_LIB_MODEL_NODE_H
#define __UNI_LIB_MODEL_NODE_H

#include "UniversumLib/UniversumLib.h"
#include "UniversumLib/type/NodeType.h"

#include "DRCore2/DRTypes.h"

#include "magic_enum/magic_enum.hpp"

/*!
 *
 * \author: Dario Rekowski
 *
 * \date: 15.11.2015
 *
 * \brief: base class for scene nodes, contains parent and child pointer
 *
 */
namespace UniLib {
	namespace model {

		class UNIVERSUMLIB_EXPORT Node
		{
		public:
			Node(Node* parent = NULL): mType(magic_enum::enum_integer(NodeType::NODE)), mParent(parent) {}
			virtual ~Node() {};

			inline Node* getParent() {return mParent;}
			inline const Node* getParent() const { return mParent;}
			// update node and child s
			virtual DRReturn move(float timeSinceLastFrame) = 0;
			inline HASH getType() const {return mType;}
			inline bool isTypeOf(NodeType type) const { auto t = magic_enum::enum_integer(type); return (mType & t) == t; }
		protected:
			int  mType;
			Node* mParent;
		};

	}
}

#endif //__UNI_LIB_MODEL_NODE_H