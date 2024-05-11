#include "UniversumLib/view/Texture.h"
#include "UniversumLib/exception/Loadable.h"

#include "DRCore2/DRCore2Main.h"

namespace UniLib {
	namespace view {

		Texture::Texture(DHASH id, const char* textureName/* = NULL*/)
			: mTextureModel(NULL), mId(id)
		{
			if (textureName) {
				mTextureName = textureName;
				setLoadingState(LoadingStateType::HAS_INFORMATIONS);
			}
		}

		Texture::Texture(DRVector2i size, GLenum format)
			: mTextureModel(new model::Texture(size, format))
		{
			mId = mTextureModel->getHash();
			setLoadingState(LoadingStateType::HAS_INFORMATIONS);
		}

		Texture::~Texture()
		{
		}		

		LoadingStateType Texture::detectLoadingState()
		{
			UNIQUE_LOCK;
			if (uploadedToGPU()) {
				return LoadingStateType::FULLY_LOADED;
			}
			if (mTextureModel && mTextureModel->hasImageData()) {
				return LoadingStateType::CPU_DATA_READY;
			}
			if (!mTextureModel && mTextureName.empty()) {
				return LoadingStateType::EMPTY;
			}

			return LoadingStateType::HAS_INFORMATIONS;
			
		}

		DRReturn Texture::load(LoadingStateType target)
		{
			UNIQUE_LOCK;
			auto state = checkLoadingState();
			if (state == LoadingStateType::FULLY_LOADED) {
				LOG_WARNING("called load but it is already loaded!");
				return DR_OK;
			}
			if (target == LoadingStateType::STORAGE_DATA_READY || target == LoadingStateType::CPU_DATA_READY)
			{
				if (state != LoadingStateType::HAS_INFORMATIONS) {
					throw exception::LoadableInvalidLoadOrder("missing information to load texture from storage", state, target);
				}
				return mTextureModel->loadFromFile(mTextureName.data());
			}
			if (target == LoadingStateType::GPU_DATA_READY) {
				if (state != LoadingStateType::CPU_DATA_READY) {
					throw exception::LoadableInvalidLoadOrder("texture data not in memory, so cannot upload to gpu", state, target);
				}
				uploadToGPU();
				return DR_OK;
			}
			return DR_ERROR;
		}
	}
}