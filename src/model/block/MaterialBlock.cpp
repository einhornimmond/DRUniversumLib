#include "UniversumLib/model/block/MaterialBlock.h"
#include "UniversumLib/lib/rapidJson.h"

#include "magic_enum/magic_enum.hpp"

using namespace rapidjson;

namespace UniLib {
	namespace model {
		namespace block {
			const char* MaterialBlock::objectTypeName = "Material";

			MaterialBlock::MaterialBlock(std::string name)
			: BlockType(name)
			{
				
			}

			MaterialBlock::~MaterialBlock() 
			{

			}

			DRReturn MaterialBlock::initFromJson(const Value& json)
			{
				lib::jsonMemberRequired(json, "base_type", JsonMemberType::STRING, objectTypeName);
				lib::jsonMemberRequired(json, "density", JsonMemberType::FLOAT, objectTypeName);
				lib::jsonMemberRequired(json, "melting_point", JsonMemberType::FLOAT, objectTypeName);
				lib::jsonMemberRequired(json, "hitpoints", JsonMemberType::INTEGER, objectTypeName);
				lib::jsonMemberRequired(json, "shader", JsonMemberType::OBJECT, objectTypeName);

				mBaseType = magic_enum::enum_cast<BlockAggregateType>(json["base_type"].GetString()).value_or(BlockAggregateType::NONE);
				if (json.HasMember("transparency") && json["transparency"].IsBool()) {
					mTransparency = json["transparency"].GetBool();
				}
				mDensity = json["density"].GetFloat();
				mMeltingPoint = json["melting_point"].GetFloat();
				mHitpoints = json["hitpoints"].GetInt();
				auto shader = json["shader"].GetObject();
				if (shader.HasMember("fragment") && shader["fragment"].IsString()) {
					mFragmentShaderName = shader["fragment"].GetString();
				}
				if (shader.HasMember("vertex") && shader["vertex"].IsString()) {
					mVertexShaderName = shader["vertex"].GetString();
				}

				return DR_OK;
			}


		}
	}
}