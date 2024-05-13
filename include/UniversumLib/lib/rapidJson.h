#ifndef __UNIVERSUM_LIB_LIB_RAPID_JSON_H
#define __UNIVERSUM_LIB_LIB_RAPID_JSON_H

#include "UniversumLib/export.h"
#include "UniversumLib/type/JsonMemberType.h"

#include "rapidjson/document.h"

#include <string>

namespace UniLib {
	namespace lib {
		UNIVERSUMLIB_EXPORT rapidjson::Document parseJsonFromString(const std::string& jsonString);

		//! check if member with type exist on obj, else throw exception
		//! \param obj rapidjson value or document
		//! \param memberName member which will be checked
		//! \param memberType type member must have
		//! \param objectName (optional) for exception message if is member is missing
		UNIVERSUMLIB_EXPORT void jsonMemberRequired(
			const rapidjson::Value& obj, const char* memberName, JsonMemberType memberType, const char* objectName = nullptr
		);
	}
}

#endif //__UNIVERSUM_LIB_LIB_RAPID_JSON_H