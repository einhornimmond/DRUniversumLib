#ifndef __UNIVERSUM_LIB_EXCEPTION_RAPID_JSON_H
#define __UNIVERSUM_LIB_EXCEPTION_RAPID_JSON_H

#include "UniversumLib.h"
#include "rapidjson/error/error.h"
#include "rapidjson/document.h"

namespace UniLib {
	namespace exception {
		class UNIVERSUMLIB_EXPORT RapidjsonParseError : public UniversumLib
		{
		public:
			explicit RapidjsonParseError(const char* what, rapidjson::ParseErrorCode parseErrorCode, size_t parseErrorOffset) noexcept;

			RapidjsonParseError& setRawText(const std::string& rawText);
			inline const std::string& getRawText() { return mRawText; }
			std::string getFullString() const;
			rapidjson::Value getDetails(rapidjson::Document::AllocatorType& alloc) const;

		protected:
			rapidjson::ParseErrorCode mParseErrorCode;
			size_t					  mParseErrorOffset;
			std::string				  mRawText;
		};

		class UNIVERSUMLIB_EXPORT RapidjsonMissingMember : public UniversumLib
		{
		public:
			explicit RapidjsonMissingMember(const char* what, const char* fieldName, const char* fieldType) noexcept;

			std::string getFullString() const;
		protected:
			std::string mFieldName;
			std::string mFieldType;

		};

		class UNIVERSUMLIB_EXPORT RapidjsonInvalidMember : public RapidjsonMissingMember
		{
		public:
			explicit RapidjsonInvalidMember(const char* what, const char* fieldName, const char* fieldType) noexcept :
				RapidjsonMissingMember(what, fieldName, fieldType) {}
		};

	}
}

#endif //__UNIVERSUM_LIB_EXCEPTION_RAPID_JSON_H