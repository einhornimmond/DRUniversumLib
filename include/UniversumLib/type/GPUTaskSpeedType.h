#ifndef __UNIVERSUM_LIB_TYPE_GPU_TASK_SPEED_TYPE_H
#define __UNIVERSUM_LIB_TYPE_GPU_TASK_SPEED_TYPE_H

#include "DRCore2/DRTypes.h"

namespace UniLib {
	enum class GPUTaskSpeedType : u8 {
		FAST = 0,
		SLOW = 1,
		LOAD = 2,
		ENTRY_COUNT = 3
	};
}

#endif // __UNIVERSUM_LIB_TYPE_GPU_TASK_SPEED_TYPE_H