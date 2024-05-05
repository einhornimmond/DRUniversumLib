#include "UniversumLib/exception/Texture.h"

namespace UniLib {
	namespace exception {
		std::string Texture::toString() 
		{
			size_t size = strlen(what()) + mFileName.size() + 12 + mErrorMsg.size() + 11 + 2;
			std::string result;
			result.reserve(size);
			result = what();
			result += ", fileName: " + mFileName + ", details: " + mErrorMsg;
			return result;
		}
	}
}