/*/*************************************************************************
 *                                                                         *
 * UniversumLib, collection of classes for generating and go through a     *
 * whole universe. It is for my Gameproject Spacecraft					   * 
 * Copyright (C) 2014, 2015, 2016, 2017 Dario Rekowski.					   *
 * Email: dario.rekowski@gmx.de   Web: www.einhornimmond.de                *
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

#ifndef __DR_UNIVERSUM_LIB_VIEW_SEKTOR_GENERATOR_H__ 
#define __DR_UNIVERSUM_LIB_VIEW_SEKTOR_GENERATOR_H__

#include "UniversumLib/export.h"

#include "DRCore2/DRTypes.h"

// Prototyp class for view classes,
// renderSector in old implemantation

namespace UniLib {
	namespace model {
		class Sector;
	}
	namespace view {

		class Camera;

		class UNIVERSUMLIB_EXPORT Sector
		{
		public:
			Sector(model::Sector* sektorModel = nullptr);
			~Sector();

			__inline void setSectorModel(model::Sector* sektorModel) {mSectorModel = mSectorModel;}

			// prototypes
			// calculate current visibility mode for given camera, multiple calls per frame possible
			virtual DRReturn updateVisibility(view::Camera* camera) = 0;
			// render sektor per camera (multiple calls pro frame possible)
			virtual DRReturn render(view::Camera* camera, float timeSinceLastFrame) = 0;

			
		protected:
			model::Sector* mSectorModel;
		private:
		};
	};
};

#endif //__DR_UNIVERSUM_LIB_VIEW_SEKTOR_GENERATOR_H__