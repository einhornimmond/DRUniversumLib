#ifndef __UNIVERSUM_LIB_EXCEPTION_LOADABLE_H
#define __UNIVERSUM_LIB_EXCEPTION_LOADABLE_H

#include "UniversumLib.h"
#include "UniversumLib/type/LoadingStateType.h"

namespace UniLib {
	namespace exception {
		class UNIVERSUMLIB_EXPORT LoadableInvalidLoadOrder : public UniversumLib
		{
		public:
			explicit LoadableInvalidLoadOrder(const char* what, LoadingStateType currentType, LoadingStateType targetType) noexcept
				: UniversumLib(what), mCurrentType(currentType), mTargetType(targetType) {}
			virtual ~LoadableInvalidLoadOrder() {}

			virtual std::string toString();
		protected:
			LoadingStateType mCurrentType;
			LoadingStateType mTargetType;

		};

		class UNIVERSUMLIB_EXPORT LoadableTargetNotSupported : public UniversumLib
		{
		public:
			explicit LoadableTargetNotSupported(const char* what, LoadingStateType target) noexcept
				: UniversumLib(what), mTargetType(target) {}

			virtual std::string toString();

		protected:
			LoadingStateType mTargetType;
		};
	}
}

#endif //__UNIVERSUM_LIB_EXCEPTION_LOADABLE_H