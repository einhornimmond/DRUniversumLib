#include "UniversumLib/lib/rapidJson.h"
#include "UniversumLib/exception/RapidJson.h"

#include "magic_enum/magic_enum.hpp"

using namespace rapidjson;

namespace UniLib {
	namespace json {
		Document parseJsonFromString(const std::string& jsonString)
		{
			Document result;
			// extract parameter from string
			result.Parse(jsonString.data());

			if (result.HasParseError()) {
				throw exception::RapidjsonParseError("error parsing json string", result.GetParseError(), result.GetErrorOffset())
					.setRawText(jsonString);
			}
			return std::move(result);
		}

		void jsonMemberRequired(
			const rapidjson::Value& obj, const char* memberName, JsonMemberType memberType, const char* objectName /*= nullptr*/
		) {
			if (!obj.HasMember(memberName)) {
				std::string what = "missing member in ";
				if (objectName) {
					what += objectName;
				}
				throw exception::RapidjsonMissingMember(what.data(), memberName, magic_enum::enum_name(memberType).data());
			}

			std::string what = "invalid member in ";
			if (objectName) {
				what += objectName;
			}

			bool wrongType = false;

			switch (memberType) {
			case JsonMemberType::STRING:
				if (!obj[memberName].IsString()) wrongType = true;
				break;
			case JsonMemberType::INTEGER:
				if (!obj[memberName].IsInt()) wrongType = true;
				break;
			case JsonMemberType::FLOAT:
				if (!obj[memberName].IsFloat()) wrongType = true;
				break;
			case JsonMemberType::NUMBER:
				if (!obj[memberName].IsNumber()) wrongType = true;
				break;
			case JsonMemberType::ARRAY:
				if (!obj[memberName].IsArray()) wrongType = true;
				break;
			case JsonMemberType::OBJECT: 
				if (!obj[memberName].IsObject()) wrongType = true;
				break;
			default: throw exception::UnknownEnum<JsonMemberType>("unknown enum value in model::graphql::Base", memberType);
			}

			if (wrongType) {
				throw exception::RapidjsonInvalidMember(what.data(), memberName, magic_enum::enum_name(memberType).data());
			}
		}
	}
}
