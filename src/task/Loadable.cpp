#include "UniversumLib/task/Loadable.h"
#include "UniversumLib/lib/Loadable.h"

namespace UniLib {
	namespace task {
		DRReturn Loadable::run()
		{
			auto result = mParent->load(mTargetLoadingState);
			mParent->updateLoadingState();
			return result;
		}
	}
}