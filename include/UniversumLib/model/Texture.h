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
 * \date: 06.03.2016
 *
 * \desc: Texture Model, contains texture pixel data
 *
 */

#ifndef __DR_UNIVERSUM_LIB_MODEL_TEXTURE_H
#define __DR_UNIVERSUM_LIB_MODEL_TEXTURE_H

#include "UniversumLib/UniversumLib.h"
#include "UniversumLib/type/ImageFileType.h"

#include "DRCore2/Threading/DRMultithreadContainer.h"
#include "DRCore2/DRTypes.h"
#include "DRCore2/Foundation/DRVector2i.h"
#include "DRCore2/Foundation/DRColor.h"


namespace UniLib {
	namespace model {
		class UNIVERSUMLIB_EXPORT Texture : public DRMultithreadContainer
		{
		public:
			Texture();
			// if texture is render target
			Texture(const DRVector2i& size, GLenum format);
			virtual ~Texture();

			// tasks
			DRReturn loadFromFile(const char* filename);
			//! \brief load image from memory
			//! \param data copy pointer, so please don't free
			DRReturn loadFromMemory(u8* data, const DRVector2i& size, GLenum format);
			DRReturn saveIntoFile(const char* filename, ImageFileType type);

			void clearMemory();

			// access data
			inline DRVector2i getSize() { return mSize; }
			inline void setSize(DRVector2i size) { mSize = size; }
			inline GLenum getFormat() { return mFormat; }
			inline DHASH getHash() { return calculateHash(mSize, mFormat); }
			inline bool hasImageData() { UNIQUE_LOCK; return mRawImageData != NULL; }
			inline u8* getPixels() { return mRawImageData; }

			static DHASH calculateHash(DRVector2i size, GLenum format);

		protected:
			u8* mRawImageData;
			DRVector2i mSize;
			GLenum mFormat;
		};
	}
}

#endif //__DR_UNIVERSUM_LIB_MODEL_TEXTURE_H