#include "UniversumLib/task/gpu/Loadable.h"
#include "UniversumLib/lib/Loadable.h"

namespace UniLib {
	namespace task {
		namespace gpu {
			DRReturn Loadable::run() {
				auto result = mParent->load(LoadingStateType::GPU_DATA_READY);
				mParent->updateLoadingState();
				return result;
			}

			bool Loadable::isReady()
			{
				return mParent->isReadyForLoad(LoadingStateType::GPU_DATA_READY);
			}
		}
	}
}