#include "UniversumLib/exception/RapidJson.h"

#include "rapidjson/error/en.h"

using namespace rapidjson;

namespace UniLib {
	namespace exception {
		RapidjsonParseError::RapidjsonParseError(const char* what, ParseErrorCode parseErrorCode, size_t parseErrorOffset) noexcept
			: UniversumLib(what), mParseErrorCode(parseErrorCode), mParseErrorOffset(parseErrorOffset)
		{

		}

		RapidjsonParseError& RapidjsonParseError::setRawText(const std::string& rawText)
		{
			mRawText = rawText;
			return *this;
		}
		std::string RapidjsonParseError::getFullString() const
		{
			std::string resultString;
			auto parseErrorCodeString = GetParseError_En(mParseErrorCode);
			std::string parseErrorOffsetString = std::to_string(mParseErrorOffset);

			size_t resultSize = strlen(what()) + strlen(parseErrorCodeString) + 15 + parseErrorOffsetString.size() + 14 + 2;
			if (mRawText.size()) {
				resultSize += mRawText.size() + 7;
			}
			resultString = what();
			resultString += ", parse error: ";
			resultString += parseErrorCodeString;
			resultString += " on position: " + parseErrorOffsetString;
			if (mRawText.size()) {
				resultString += ", src: " + mRawText;
			}
			return resultString;
		}

		Value RapidjsonParseError::getDetails(Document::AllocatorType& alloc) const
		{
			Value details(kObjectType);
			details.AddMember("what", Value(what(), alloc), alloc);
			details.AddMember("parseErrorCode", Value(GetParseError_En(mParseErrorCode), alloc), alloc);
			details.AddMember("parseErrorPosition", mParseErrorOffset, alloc);
			if (mRawText.size()) {
				details.AddMember("src", Value(mRawText.data(), alloc), alloc);
			}

			return std::move(details);
		}

		// ************************** Missing Member in Rapidjson Object ********************
		RapidjsonMissingMember::RapidjsonMissingMember(const char* what, const char* fieldName, const char* fieldType) noexcept
			: UniversumLib(what), mFieldName(fieldName), mFieldType(fieldType)
		{

		}

		std::string RapidjsonMissingMember::getFullString() const
		{
			std::string result;
			result = what();
			if (mFieldName.size()) {
				result += ", field name: " + mFieldName;
			}
			if (mFieldType.size()) {
				result += ", field type: " + mFieldType;
			}
			return result;
		}
	}
}