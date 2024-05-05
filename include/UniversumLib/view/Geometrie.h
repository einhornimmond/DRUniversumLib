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
 * \author: Dario Rekowski
 *
 * \date: 23.01.2016
 *
 * \desc: Base interface for geometrie view, get geometrie datat to gpu and rendered
 */

#ifndef __UNIVERSUM_LIB_VIEW_GEOMETRIE_H
#define __UNIVERSUM_LIB_VIEW_GEOMETRIE_H

#include "UniversumLib/export.h"
#include "UniversumLib/task/gpu/Task.h"
#include "UniversumLib/lib/Loadable.h"

#include "DRCore2/DRTypes.h"
#include "DRCore2/Foundation/DRIResource.h"

#include <memory>

namespace UniLib {
	namespace model {
		namespace geometrie {
			class BaseGeometrie;
			typedef std::shared_ptr<BaseGeometrie> BaseGeometriePtr;
		}
	}
	namespace view {

		class UNIVERSUMLIB_EXPORT Geometrie : public DRIResource, public lib::Loadable
		{
		public:
			Geometrie(model::geometrie::BaseGeometriePtr baseGeometrie);
			Geometrie();
			virtual ~Geometrie();

			virtual DRReturn render() = 0;

			inline void setBaseGeometrie(model::geometrie::BaseGeometriePtr baseGeometrie) {
				mGeometrieModel = baseGeometrie;
				if (checkLoadingState() == LoadingStateType::EMPTY) {
					setLoadingState(LoadingStateType::HAS_INFORMATIONS);
				}
			}		

			virtual const char* getResourceType() const {return "view::Geometrie";}
			// simple compare pointer adresses
			virtual bool less_than(DRIResource& b) const {return this < &b;}
		protected:
			model::geometrie::BaseGeometriePtr mGeometrieModel;

		};

		typedef std::shared_ptr<Geometrie> GeometriePtr;


		
		
	}
}



#endif //__UNIVERSUM_LIB_VIEW_GEOMETRIE_H