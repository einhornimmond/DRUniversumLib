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



#ifndef __UNI_LIB_MODEL_POSITION_H
#define __UNI_LIB_MODEL_POSITION_H

#include "UniversumLib/export.h"

#include "DRCore2/Foundation/DRVector3.h"
#include "DRCore2/Foundation/DRMatrix.h"

/*!
 *
 * \author: Dario Rekowski
 *
 * \date 15.11.2015
 *
 * \brief simply represent a position (and scale) 
 *
 *
 */

namespace UniLib {
	namespace model {

		class UNIVERSUMLIB_EXPORT Position
		{
		public:
			Position(const DRVector3& pos = DRVector3(0.0f), const DRVector3& scale = DRVector3(1.0f));
			~Position();

			inline void setPosition(const DRVector3& pos) {mPosition = pos;}
			inline const DRVector3& getPosition() const {return mPosition;}
			inline void move(const DRVector3& diff) {mPositionAdd += diff;}
			inline void moveAbs(const DRVector3& diff) { mPosition += diff; }

			inline void setScale(const DRVector3& scale) {mScale = scale;}
			inline const DRVector3& getScale() const {return mScale;}

			inline const DRVector3& getPositionAdd() const { return mPositionAdd; }
			inline void setPositionAdd(const DRVector3& positionAdd) { mPositionAdd = positionAdd; }

			//! \brief calculate matrix from position
			//! \param mat if object has also rotation, give mat to add position changes relative
			DRMatrix calculateMatrix(const DRMatrix& mat = DRMatrix::identity());

		protected:
			DRVector3 mPosition;
			DRVector3 mPositionAdd;
			DRVector3 mScale;
		};
	}

}

#endif //__UNI_LIB_MODEL_POSITION_H