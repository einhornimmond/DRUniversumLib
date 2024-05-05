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


#ifndef __DR_UNIVERSUM_LIB_VIEW_TEXTURE_H
#define __DR_UNIVERSUM_LIB_VIEW_TEXTURE_H

#include "UniversumLib/lib/Loadable.h"
#include "UniversumLib/manager/Textures.h"
#include "UniversumLib/model/Texture.h"
#include "UniversumLib/type/LoadingStateType.h"

#include "DRCore2/Threading/DRTask.h"
#include "DRCore2/DRTypes.h"
#include "DRCore2/Foundation/DRIResource.h"

namespace UniLib {
	namespace view {	
		class UNIVERSUMLIB_EXPORT Texture: public lib::Loadable, public DRIResource
		{
		public:
			Texture(DHASH id, const char* textureName = NULL);
			Texture(DRVector2i size, GLenum format);
			virtual ~Texture();

			void saveIntoFile(const char* filename);
			//! \brief load image from memory, release data in texture manager thread			
			DRReturn loadFromMemory(u8* data, DRCommand* finishCommand = NULL);
			DRReturn saveIntoFile(const char* filename, u8* data);

			// virtuals, contains renderer specific code
			virtual void uploadToGPU() = 0;
			virtual void downloadFromGPU() = 0;
			virtual bool uploadedToGPU() = 0;
			virtual void bind() = 0;
			virtual GLuint getTextureId() = 0;
			// virtuals from DRIResource
			virtual const char* getResourceType() const { return "view::Texture"; }
			virtual bool less_than(DRIResource& b) const {
				return mId < static_cast<Texture&>(b).mId;
			}

			// access parameters
			inline DHASH getId() { return mId; }
			inline std::string getFilename() { return mTextureName; }
			inline u32 getTimeout() { return mTimeout; }
			inline void updateTimeout(u32 passingTime) { mTimeout -= passingTime; }
			inline void setTimeout(u32 timeout) { mTimeout = timeout; }

			inline DRVector2i getTextureSize() { return mTextureModel->getSize(); }
			//! detect current loading state
			LoadingStateType detectLoadingState();
			//! actuall load code
			virtual DRReturn load(LoadingStateType target);

		protected:
			std::shared_ptr<model::Texture> mTextureModel;
			std::string mTextureName;

			DHASH mId;
			u32 mTimeout;
		};
		
	}
}


#endif //__DR_UNIVERSUM_LIB_VIEW_TEXTURE_H

