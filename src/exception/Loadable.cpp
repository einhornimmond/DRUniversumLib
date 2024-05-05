#include "UniversumLib/exception/Loadable.h"

#include "magic_enum/magic_enum_iostream.hpp"

#include <sstream>

using magic_enum::iostream_operators::operator<<;

namespace UniLib {
	namespace exception {
		std::string LoadableInvalidLoadOrder::toString()
		{
			std::stringstream s;
			s << what() << ", current" << mCurrentType << ", target: " << mTargetType;
			return s.str();
		}
	}
}