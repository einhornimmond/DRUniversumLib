#include "UniversumLib/view/Material.h"
#include "UniversumLib/model/ShaderProgram.h"

namespace UniLib {
	namespace view {
		Material::Material() 
			: mUniformsSet(NULL)
		{

		}

		Material::~Material()
		{

		}

		LoadingStateType Material::checkLoadingState()
		{
			if (mShaderProgram && mShaderProgram->checkLoadingState() == LoadingStateType::FULLY_LOADED && mUniformsSet) {
				return LoadingStateType::FULLY_LOADED;
			}
			if (!mShaderProgram || !mUniformsSet) {
				return LoadingStateType::EMPTY;
			}
			return mShaderProgram->checkLoadingState();
		}
		
	}
}