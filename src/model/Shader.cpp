#include "UniversumLib/model/Shader.h"
#include "UniversumLib/exception/Loadable.h"

#include "DRCore2/Manager/DRFileManager.h"
#include "DRCore2/DRCore2Main.h"
#include "DRCore2/Foundation/DRHash.h"

#include "magic_enum/magic_enum.hpp"

namespace UniLib {
	namespace model {
		Shader::Shader(const char* shaderFileName, ShaderType shaderType)
			: lib::Loadable(LoadingStateType::HAS_INFORMATIONS), mType(shaderType), mFileName(shaderFileName), mID(DRMakeFilenameHash(shaderFileName))
		{
		}

		Shader::Shader(const model::ShaderInformation& infos)
			: lib::Loadable(LoadingStateType::HAS_INFORMATIONS), 
			mType(infos.type), mFileName(infos.fileName),
			mID(DRMakeFilenameHash(infos.fileName.data()))
		{

		}

		Shader::~Shader()
		{
		}


		DRReturn Shader::load(LoadingStateType target)
		{
			UNIQUE_LOCK;
			auto state = detectLoadingState();
			if (LoadingStateType::STORAGE_DATA_READY == target) {
				if (LoadingStateType::HAS_INFORMATIONS != state) {
					throw exception::LoadableInvalidLoadOrder("missing information to load shader from storage", state, target);
				}
				loadFromFile();
				asyncLoad(LoadingStateType::GPU_DATA_READY);
				return DR_OK;
			}
			if (LoadingStateType::GPU_DATA_READY == target) {
				if (LoadingStateType::STORAGE_DATA_READY != state) {
					throw exception::LoadableInvalidLoadOrder("missing information to load shader onto gpu", state, target);
				}
				return compileOnGPU();
			}
			DRLog.writeToLog("shader loading target: %s", magic_enum::enum_name(target).data());
			LOG_ERROR("invalid target for shader load", DR_ERROR);
		}

		void Shader::loadFromFile()
		{
			const char* path = DRFileManager::Instance().getWholePfad(mFileName.data());
			std::string complete;
			if (path) {
				complete = std::string(path) + std::string("/") + mFileName;
			}
			else {
				complete = mFileName;
			}

			DRFile file(complete.data(), "rb");
			if (!file.isOpen()) {
				DRLog.writeToLog("couldn't find shader file: %s", mFileName.data());
				LOG_ERROR_VOID("cannot open file");
			}

			int bytesinfile = file.getSize();
			mShaderSource.resize(bytesinfile, 0);
			size_t bytesread = 0;
			file.read(mShaderSource.data(), 1, bytesinfile, &bytesread);
			setLoadingState(LoadingStateType::STORAGE_DATA_READY);
		}

		LoadingStateType Shader::detectLoadingState()
		{
			UNIQUE_LOCK;
			if (mFileName.empty()) {
				return LoadingStateType::EMPTY;
			}
			if (parsedOnGPU()) {
				return LoadingStateType::FULLY_LOADED;
			}
			if (!mShaderSource.empty()) {
				return LoadingStateType::STORAGE_DATA_READY;
			}
			return LoadingStateType::HAS_INFORMATIONS;
		}
	}
}