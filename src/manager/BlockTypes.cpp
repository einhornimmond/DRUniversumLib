#include "UniversumLib/manager/BlockTypes.h"
#include "UniversumLib/model/block/MaterialBlock.h"
#include "UniversumLib/exception/Loadable.h"
#include "UniversumLib/lib/rapidJson.h"

#include "DRCore2/Utils/DRProfiler.h"
#include "DRCore2/Foundation/DRFile.h"
#include "DRCore2/DRCore2Main.h"

using namespace rapidjson;

namespace UniLib {
	namespace manager {

		// ************************************************************************************************++
		// BLock Material Manager
		// ************************************************************************************************++

		BlockTypeManager::BlockTypeManager() 
			: lib::Loadable(LoadingStateType::EMPTY)
		{

		}

		BlockTypeManager::~BlockTypeManager()
		{
			exit();
		}

		BlockTypeManager* BlockTypeManager::getInstance()
		{
			static BlockTypeManager theOne;
			return &theOne;
		}
		// called from io Thread or directly
		DRReturn BlockTypeManager::init(std::vector<std::string> materialConfigFiles)
		{
			mMaterialConfigFileNames = std::move(materialConfigFiles);
			setLoadingState(LoadingStateType::HAS_INFORMATIONS);
			asyncLoad(LoadingStateType::STORAGE_DATA_READY);
			return DR_OK;
		}
	
		model::block::BlockType* BlockTypeManager::getBlockType(HASH id)
		{
			UNIQUE_LOCK;
			auto it = mBlockTypes.find(id);
			if (it != mBlockTypes.end()) {
				return it->second;
			}
			return nullptr;
		}

		DRReturn BlockTypeManager::load(LoadingStateType target)
		{
			UNIQUE_LOCK;
			auto state = detectLoadingState();
			if (LoadingStateType::STORAGE_DATA_READY == target) {
				if (LoadingStateType::HAS_INFORMATIONS != state) {
					throw exception::LoadableInvalidLoadOrder("missing information for reading block type json files", state, target);
				}
				for (auto& configFile : mMaterialConfigFileNames) {
					DRFile file;
					file.open(configFile.data(), false, "rt");
					mMaterialConfigFileContents.push_back(file.readAsString());
				}
				setLoadingState(LoadingStateType::STORAGE_DATA_READY);
				asyncLoad(LoadingStateType::CPU_DATA_READY);
			}
			else if (LoadingStateType::CPU_DATA_READY == target) {
				if (LoadingStateType::STORAGE_DATA_READY != state) {
					throw exception::LoadableInvalidLoadOrder("missing information for parsing block type json files", state, target);
				}
				for (auto& configFile : mMaterialConfigFileContents) {
					auto result = parsingJsonToBlockTypes(configFile);
					if (!result) {
						LOG_ERROR("error parsing block type config file", DR_ERROR);
					}
				}
			}
		}

		LoadingStateType BlockTypeManager::detectLoadingState()
		{
			UNIQUE_LOCK;
			if (mBlockTypes.size()) {
				return LoadingStateType::FULLY_LOADED;
			} else if (mMaterialConfigFileContents.size()) {
				return LoadingStateType::STORAGE_DATA_READY;
			} else if (mMaterialConfigFileNames.size()) {
				return LoadingStateType::HAS_INFORMATIONS;
			}
			return LoadingStateType::EMPTY;
		}

		void BlockTypeManager::exit()
		{
			UNIQUE_LOCK;
			for(auto it = mBlockTypes.begin(); it != mBlockTypes.end(); it++) {
				delete it->second;
			}
			mBlockTypes.clear();
		}

		DRReturn BlockTypeManager::parsingJsonToBlockTypes(const std::string& fileContent)
		{
			DRProfiler profiler;
			auto json = lib::parseJsonFromString(fileContent);
			auto material = json.FindMember("materialTypes");
			if (material == json.MemberEnd()) {
				return DR_OK;
			}
			if (material->value.IsArray()) {
				for (auto& entry: material->value.GetArray())
				{
					lib::jsonMemberRequired(entry, "name", JsonMemberType::STRING, model::block::MaterialBlock::objectTypeName);
					auto name = entry["name"].GetString();
					auto id = DRMakeStringHash(name);
					auto blockTypesIt = mBlockTypes.find(id);
					if (blockTypesIt != mBlockTypes.end()) {
						if (std::string(blockTypesIt->second->getName()) != name) {
							DRLog.writeToLog("Material %s and Material %s have the same hash: %d",
								blockTypesIt->second->getName(), name, id);
							LOG_ERROR("hash collision", DR_ERROR);
						}
						else {
							DRLog.writeToLog("material: %s", name);
							LOG_WARNING("One material was declared more than once, use only first declaration");
						}
					}
					else {
						model::block::MaterialBlock* mat = new model::block::MaterialBlock(name);
						if (mat->initFromJson(entry)) {
							delete mat;
							LOG_ERROR("error by init one material", DR_ERROR);
						}
						mat->setId(id);
						mBlockTypes.insert({ id, mat });
					}
				}
			}
			else {
				LOG_ERROR("json isn't a array", DR_ERROR);
			}
			DRLog.writeToLog("[BlockTypeManager::parsingJsonToBlockTypes] running time: %s", profiler.string().data());
			return DR_OK;
		}
	}
}