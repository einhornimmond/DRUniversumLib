#ifndef __UNIVERSUM_LIB_EXCEPTION_UNIVERSUM_LIB_H
#define __UNIVERSUM_LIB_EXCEPTION_UNIVERSUM_LIB_H

#include "UniversumLib/export.h"

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
	}
}

#endif //__UNIVERSUM_LIB_EXCEPTION_UNIVERSUM_LIB_H