#ifndef __UNIVERSUM_LIB_EXCEPTION_UNIVERSUM_LIB_H
#define __UNIVERSUM_LIB_EXCEPTION_UNIVERSUM_LIB_H

#include "UniversumLib/export.h"

#include "magic_enum/magic_enum.hpp"

#include <stdexcept>
#include <string>

namespace UniLib {
	namespace exception {

		class UNIVERSUMLIB_EXPORT UniversumLib : public std::runtime_error
		{
		public:
			explicit UniversumLib(const char* what) noexcept : std::runtime_error(what) {}
			virtual ~UniversumLib() {}
			virtual std::string toString() { return what(); }
		protected:
		};

		template<typename T>
		class UNIVERSUMLIB_EXPORT InvalidEnum : public UniversumLib
		{
		public:
			template<typename T>
			explicit InvalidEnum(const char* what, T enumValue) noexcept
				: UniversumLib(what), mEnumValue(enumValue) {};

			template<typename T>
			std::string getFullString() const {
				std::string resultString;
				auto enumString = magic_enum::enum_name(mEnumValue);
				size_t resultSize = strlen(what()) + enumString.size() + 10;
				resultString.reserve(resultSize);
				resultString = what();
				resultString += ", with: " + enumString;
				return resultString;
			};

		protected:
			T mEnumValue;
		};

		template<typename T>
		class UNIVERSUMLIB_EXPORT UnknownEnum : public InvalidEnum<T>
		{
		public:
			template<typename T>
			explicit UnknownEnum(const char* what, T enumValue) noexcept
				: InvalidEnum(what, enumValue) {}

			template<typename T>
			std::string getFullString() const
			{
				std::string resultString;
				auto enumString = magic_enum::enum_type_name<decltype(mEnumValue)>();
				auto valueString = std::to_string(magic_enum::enum_integer(mEnumValue));
				size_t resultSize = strlen(what()) + enumString.size() + valueString.size() + 2 + 13 + 9;
				resultString.reserve(resultSize);
				resultString = what();
				resultString += ", enum name: " + enumString;
				resultString += ", value: " + valueString;
				return resultString;
			}
		};

		template<typename T>
		class UNIVERSUMLIB_EXPORT UnhandledEnum : public UnknownEnum<T>
		{
		public:
			template<typename T>
			explicit UnhandledEnum(const char* what, T enumValue) noexcept
				: UnknownEnum(what, enumValue) {}
		};
	}
}

#endif //__UNIVERSUM_LIB_EXCEPTION_UNIVERSUM_LIB_H