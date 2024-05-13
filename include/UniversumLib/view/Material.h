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

#ifndef __UNIVERSUM_LIB_VIEW_MATERIAL_H
#define __UNIVERSUM_LIB_VIEW_MATERIAL_H

#include "UniversumLib/export.h"
#include "UniversumLib/type/LoadingStateType.h"

#include "DRCore2/Foundation/DRIResource.h"

#include <memory>

namespace UniLib {
	namespace model {
		class ShaderProgram;
		typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;

		class UniformSet;
	}
	namespace view {

		class Texture;
		typedef std::shared_ptr<Texture> TexturePtr;

		class UNIVERSUMLIB_EXPORT Material : public DRIResource
		{
		public:
			Material();
			virtual ~Material();

			virtual void bind() = 0;
			inline void setShaderProgram(model::ShaderProgramPtr shaderProgram) { mShaderProgram = shaderProgram; }
			inline model::ShaderProgramPtr getShaderProgram() {return mShaderProgram;}

			virtual const char* getResourceType() const {return "Material";}
			virtual bool less_than(DRIResource& b) const {return this < &b;}
			virtual bool hasTexture() { return false; }
			virtual bool hasMultiTexture() { return false; }

			inline void setUniformSet(model::UniformSet* uniforms) {mUniformsSet = uniforms;}
			inline model::UniformSet* const getUniformSet() const {return mUniformsSet;}

			// check loading state
			virtual LoadingStateType checkLoadingState();

		protected:
			model::ShaderProgramPtr mShaderProgram;
			model::UniformSet* mUniformsSet;
		};

		typedef std::shared_ptr<Material> MaterialPtr;
	}
}

#endif //__UNIVERSUM_LIB_VIEW_MATERIAL_H