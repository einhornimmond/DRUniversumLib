#include "UniversumLib/view/MultiTextureMaterial.h"
#include "UniversumLib/view/Texture.h"
#include "UniversumLib/manager/Textures.h"

namespace UniLib {
	namespace view {
		MultiTextureMaterial::MultiTextureMaterial(size_t countTextures)
			: mTextures(new TexturePtr[countTextures]), mTextureCount(countTextures)
		{
		}

		MultiTextureMaterial::~MultiTextureMaterial()
		{
			DR_SAVE_DELETE_ARRAY(mTextures);
		}

		void MultiTextureMaterial::usingTexture(const char* filename, size_t index)
		{
			assert(index < mTextureCount);
			manager::Textures* t = manager::Textures::getInstance();
			mTextures[index] = t->getTexture(filename);
		}
	}
}