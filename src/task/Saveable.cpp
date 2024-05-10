#include "UniversumLib/task/Saveable.h"
#include "UniversumLib/lib/Saveable.h"

namespace UniLib {
	namespace task {
		DRReturn Saveable::run() 
		{
			return mParent->saveIntoFile();
		}
	}
}