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

#ifndef __DR_UNIVERSUM_LIB_VIEW_CAMERA_GENERATOR_H__ 
#define __DR_UNIVERSUM_LIB_VIEW_CAMERA_GENERATOR_H__

#include "UniversumLib/model/MoveableNode.h"

#include "DRCore2/Foundation/DRVector2.h"

namespace UniLib {
	namespace view {
		class UNIVERSUMLIB_EXPORT Camera : public model::MoveableNode {
		public:		
			Camera(float fov = 90.0f, float nearClipping = 0.1f, float farClipping = 100.0f);
			virtual ~Camera();

			inline void setFov(float fov) {mFOV = fov;}
			inline void setNearClipping(float nearClipping) {mClipping.x= nearClipping;}
			inline void setFarClipping(float farClipping) {mClipping.y = farClipping;}
			inline void setAspectRatio(float aspectRatio) {mAspectRatio = aspectRatio;}

			inline const DRMatrix& getCameraMatrix() {return mCameraMatrix;}

			void updateCameraMatrix();
		protected:
			// field of view
			float mFOV;
			float mAspectRatio;
			DRVector2 mClipping;

			DRMatrix mCameraMatrix;
		};
	};
};

#endif //__DR_UNIVERSUM_LIB_VIEW_CAMERA_GENERATOR_H__