#ifndef __UNIVERSUM_LIB_EXCEPTION_TEXTURE_H
#define __UNIVERSUM_LIB_EXCEPTION_TEXTURE_H

#include "UniversumLib.h"

namespace UniLib {
	namespace exception {
		class UNIVERSUMLIB_EXPORT Texture : public UniversumLib 
		{
		public:
			explicit Texture(const char* what, const char* fileName, const char* errorMsg = nullptr) noexcept 
				: UniversumLib(what), mFileName(fileName), mErrorMsg(errorMsg) {}
			virtual ~Texture() {}

			virtual std::string toString();

		protected:
			std::string mFileName;
			std::string mErrorMsg;
		};

		class LoadTexture : public Texture 
		{
		public:
			explicit LoadTexture(const char* what, const char* fileName, const char* errorMsg = nullptr) noexcept
				: Texture(what, fileName, errorMsg) {}
			virtual ~LoadTexture() {}
		};
	}
}

#endif //__UNIVERSUM_LIB_EXCEPTION_TEXTURE_H