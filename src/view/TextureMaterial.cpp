#include "UniversumLib/view/TextureMaterial.h"
#include "UniversumLib/view/Texture.h"
#include "UniversumLib/manager/Textures.h"

#include "magic_enum/magic_enum.hpp"

namespace UniLib {
	namespace view {
		TextureMaterial::TextureMaterial()
		{

		}

		TextureMaterial::~TextureMaterial()
		{

		}

		void TextureMaterial::usingTexture(const char* filename)
		{
			manager::Textures* t = manager::Textures::getInstance();
			mTexture = t->getTexture(filename);
		}

		LoadingStateType TextureMaterial::checkLoadingState()
		{
			auto materialLoadingState = magic_enum::enum_integer(Material::checkLoadingState());
			auto textureLoadingState = magic_enum::enum_integer(mTexture ? mTexture->checkLoadingState() : LoadingStateType::EMPTY);
			auto minLoadingState = (materialLoadingState < textureLoadingState) ? materialLoadingState : textureLoadingState;
			return magic_enum::enum_cast<LoadingStateType>(minLoadingState).value();
		}
	}
}