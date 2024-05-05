#ifndef __UNIVERSUM_LIB_EXCEPTION_TASK_H
#define __UNIVERSUM_LIB_EXCEPTION_TASK_H

#include "UniversumLib.h"

namespace UniLib {
	namespace exception {
		class UNIVERSUMLIB_EXPORT TaskOrderException : public UniversumLib
		{
		public:
			explicit TaskOrderException(const char* what) noexcept : UniversumLib(what) {}
			virtual ~TaskOrderException() {}
		protected:

		};
	}
}

#endif //__UNIVERSUM_LIB_EXCEPTION_TASK_H