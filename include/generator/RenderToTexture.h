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
* \date: 17.03.16
*
* \desc: Prototype for render to texture tasks
*/

#ifndef __DR_UNIVERSUM_LIB_GENERATOR_RENDER_TO_TEXTURE_H
#define __DR_UNIVERSUM_LIB_GENERATOR_RENDER_TO_TEXTURE_H

#include "controller/GPUTask.h"


namespace UniLib {
	namespace view {
		class Texture;
		class Material;
		class Geometrie;
		class FrameBuffer;
		typedef DRResourcePtr<Texture> TexturePtr;
		typedef DRResourcePtr<Material> MaterialPtr;
		typedef DRResourcePtr<Geometrie> GeometriePtr;
		
	}
	namespace generator {
		/*!
		 * \brief: rendering a simple plane into texture, the real magic happens inside shader
		*/
		class UNIVERSUM_LIB_API RenderToTexture : public controller::GPUTask
		{
		public:
			RenderToTexture(view::TexturePtr texture);
			RenderToTexture();
			virtual ~RenderToTexture();
			virtual DRReturn render();
			virtual bool    isReady();
			virtual DRReturn run();

			void setMaterial(view::MaterialPtr mat);
			inline view::MaterialPtr getMaterial() { return mMaterial; }

			inline void setGeometrie(view::GeometriePtr geometrie) { mGeometrie = geometrie; }
			inline view::GeometriePtr getGeometrie() { return mGeometrie;  }

			virtual const char* getResourceType() const { return "RenderToTexture"; }
		protected:
			view::TexturePtr mTexture;
			view::MaterialPtr mMaterial;
			view::FrameBuffer* mFrameBuffer;
			view::GeometriePtr mGeometrie;
		};
	}
}

#endif //__DR_UNIVERSUM_LIB_GENERATOR_RENDER_TO_TEXTURE_H