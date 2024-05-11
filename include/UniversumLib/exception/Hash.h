#ifndef __UNIVERSUM_LIB_EXCEPTION_HASH_H
#define __UNIVERSUM_LIB_EXCEPTION_HASH_H

#include "UniversumLib.h"

namespace UniLib {
	namespace exception {
		class UNIVERSUMLIB_EXPORT HashCollision : public UniversumLib
		{
		public:
			explicit HashCollision(const char* what, const char* string1, const char* string2) noexcept
				: UniversumLib(what), mString1(string1), mString2(string2) {}
			virtual ~HashCollision() {}
			virtual std::string toString();

		protected:
			std::string mString1;
			std::string mString2;
		};
	}
}

#endif //__UNIVERSUM_LIB_EXCEPTION_HASH_H