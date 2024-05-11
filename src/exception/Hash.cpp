#include "UniversumLib/exception/Hash.h"

namespace UniLib {
	namespace exception {
		std::string HashCollision::toString()
		{
			std::string result;
			size_t size = strlen(what()) + 2 + mString1.size() + 5 + mString2.size() + 19 + 2;
			result.reserve(size);
			result = what();
			result += ", " + mString1 + " and " + mString2 + " gave the same hash";
			return result;
		}
	}
}