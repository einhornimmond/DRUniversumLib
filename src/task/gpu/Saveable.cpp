#include "UniversumLib/task/gpu/Saveable.h"
#include "UniversumLib/lib/Saveable.h"

namespace UniLib {
	namespace task {
		namespace gpu {
			DRReturn Saveable::run() {
				return mParent->downloadFromGPU();
			}
		}
	}
}