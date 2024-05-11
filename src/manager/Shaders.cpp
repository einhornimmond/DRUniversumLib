#include "Universumlib/manager/Shaders.h"
#include "Universumlib/controller/BindToRenderer.h"
#include "UniversumLib/exception/Hash.h"

#include "DRCore2/DRCore2Main.h"
#include "DRCore2/Foundation/DRHash.h"

namespace UniLib {
	namespace manager {
	using namespace model;

	

		ShaderManager::ShaderManager()
			: mInitalized(false)
		{

		}

		ShaderManager::ShaderManager(const ShaderManager&)
			: mInitalized(false)
		{

		}

		ShaderManager* const ShaderManager::getInstance() 
		{
			static ShaderManager TheOneAndOnly;
			return &TheOneAndOnly;
		}
		
		DRReturn ShaderManager::init(const char* shaderBasePath)
		{
			mShaderBasePath = shaderBasePath;
			mInitalized = true;
			LOG_INFO("ShaderManager initalisiert");
			return DR_OK;
		}

		void ShaderManager::exit()
		{
			mInitalized = false;

			mShaderProgramEntrys.clear();    

			LOG_INFO("ShaderManager beendet");
		}

		DHASH ShaderManager::makeShaderHash(const char* shaderProgramName)
		{
			DHASH hash = DRMakeStringHash(shaderProgramName);
#ifdef DEBUG
			auto it = mHashCollisionCheckMap.find(hash);
			if(it != mHashCollisionCheckMap.end()) {
				if(std::string(shaderProgramName) != it->second) {
					throw exception::HashCollision("hash collision in ShaderManager", shaderProgramName, it->second.data());
				}
			} else {
				mHashCollisionCheckMap.insert({ hash, std::string(shaderProgramName) });
			}
#endif
			return hash;
		}

		model::ShaderProgramPtr ShaderManager::getShaderProgram(DHASH id)
		{
			UNIQUE_LOCK;
			if(mShaderProgramEntrys.find(id) != mShaderProgramEntrys.end()) {
				return mShaderProgramEntrys[id];
			}
			return NULL;
		}
			
		//!
		ShaderProgramPtr ShaderManager::getShaderProgram(const char* shaderProgramName, const std::vector<model::ShaderInformation>& shaderInformations)
		{
			if(!mInitalized) return NULL;
			if(!g_RenderBinder) LOG_ERROR("render binder is not set", NULL);

			//Schauen ob schon vorhanden
			DHASH id = makeShaderHash(shaderProgramName);
			ShaderProgramPtr exist = getShaderProgram(id);
			if (exist) return exist;

			ShaderProgramPtr shaderProgram;
			ShaderProgamBinaryPtr shaderProgramBinaryPtr(g_RenderBinder->newShaderProgamBinary(shaderProgramName));
			if (shaderProgramBinaryPtr->isFileExist()) {
				shaderProgramBinaryPtr->asyncLoad(LoadingStateType::STORAGE_DATA_READY);
				shaderProgram = ShaderProgramPtr(g_RenderBinder->newShaderProgram(shaderProgramName, shaderProgramBinaryPtr, id));
			} else {
				std::vector<ShaderPtr> shaders;
				shaders.reserve(shaderInformations.size());
				for (auto info : shaderInformations) {
					shaders.push_back(getShader(info));
				}
				ShaderProgramPtr shaderProgram(g_RenderBinder->newShaderProgram(shaderProgramName, std::move(shaders), id));
			}
			shaderProgram->asyncLoad(LoadingStateType::GPU_DATA_READY);
			
			UNIQUE_LOCK;
			if (!mShaderProgramEntrys.insert({ id, shaderProgram }).second) {
				LOG_ERROR("Unerwarteter Fehler in ShaderManager::getShaderProgram aufgetreten", nullptr);
			}
			return shaderProgram;
		}

		ShaderPtr ShaderManager::getShader(const model::ShaderInformation& shaderInfos)
		{
			if(!mInitalized) return NULL;
			if(!g_RenderBinder) LOG_ERROR("render binder is not set", NULL);

			DHASH id = makeShaderHash(shaderInfos.fileName.data());

			//Schauen ob schon vorhanden
			UNIQUE_LOCK;
			if(mShaderEntrys.find(id) != mShaderEntrys.end()) {
				return mShaderEntrys[id];
			}

			ShaderPtr shader(g_RenderBinder->newShader(shaderInfos));
			shader->asyncLoad(LoadingStateType::STORAGE_DATA_READY);

			if (!mShaderEntrys.insert({ id, shader }).second) {
				LOG_ERROR("Unerwarteter Fehler in ShaderManager::getShader aufgetreten", nullptr);
			}
			return shader;
		}
	}
}

