#include "UniversumLib/model/ShaderProgram.h"
#include "UniversumLib/exception/Loadable.h"

#include "DRCore2/Foundation/DRHash.h"

namespace UniLib {
	namespace model {


		ShaderProgram::ShaderProgram(const char* name, std::vector<ShaderPtr> shaders, HASH id/* = 0*/)
		: mId(id), mName(name), mShaders(std::move(shaders))
		{
			if (!id) id = DRMakeStringHash(name);
		}

		ShaderProgram::ShaderProgram(const char* name, ShaderProgamBinaryPtr shaderProgramBinary, HASH id/* = 0*/)
			: mId(id), mName(name), mShaderProgramBinary(shaderProgramBinary)
		{
			if (!id) id = DRMakeStringHash(name);
		}


		ShaderProgram::~ShaderProgram()
		{

		}

		DRReturn ShaderProgram::load(LoadingStateType target)
		{
			if (target != LoadingStateType::GPU_DATA_READY) {
				throw exception::LoadableTargetNotSupported("target not supported for shader program", target);
			}
			return attachShaderToProgam();
		}

		bool ShaderProgram::isReadyForLoad(LoadingStateType target)
		{
			if (mShaders.size()) {
				for (auto shader : mShaders) {
					if (shader->checkLoadingState() != LoadingStateType::FULLY_LOADED) {
						return false;
					}
				}
				return true;
			}
			if (mShaderProgramBinary) {
				return mShaderProgramBinary->checkLoadingState() == LoadingStateType::FULLY_LOADED;
			}
			throw exception::LoadableInvalidLoadOrder("missing information for loading shader program", detectLoadingState(), target);
		}
	}
}