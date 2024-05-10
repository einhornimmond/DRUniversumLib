#ifndef __UNIVERSUM_LIB_MODEL_SAVE_TEXTURE_H
#define __UNIVERSUM_LIB_MODEL_SAVE_TEXTURE_H

#include "Texture.h"
#include "UniversumLib/lib/Saveable.h"

namespace UniLib {
	namespace model {
		class UNIVERSUMLIB_EXPORT SaveTexture : public lib::Saveable
		{
		public:
			//!
			//! \param stb_image_write File Type
			SaveTexture(std::shared_ptr<Texture> texture, const char* fileName, ImageFileType type) 
				: mModel(texture), mFileName(fileName), mImageFileType(type) {}

			// ------  implemented from saveable -------
			inline DRReturn saveIntoFile() { return mModel->saveIntoFile(mFileName.data(), mImageFileType);}
			// -
		protected:
			std::shared_ptr<Texture> mModel;
			std::string mFileName;
			ImageFileType mImageFileType;

		};
	}
}

#endif //__UNIVERSUM_LIB_MODEL_SAVE_TEXTURE_H