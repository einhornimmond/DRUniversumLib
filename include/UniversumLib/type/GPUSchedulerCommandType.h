#ifndef __UNIVERSUM_LIB_TYPE_GPU_SCHEDULER_COMMAND_TYPE_H
#define __UNIVERSUM_LIB_TYPE_GPU_SCHEDULER_COMMAND_TYPE_H

#include "DRCore2/DRTypes.h"

namespace UniLib {
	/*
	* define order for gpu render calls
	*/
	enum class GPUSchedulerCommandType : u8 {
		BEFORE_PREPARE_RENDERING = 0,
		PREPARE_RENDERING = 1,
		RENDERING = 2,
		AFTER_RENDERING = 3,
		AFTER_AFTER_RENDERING = 4,
		ENTRY_COUNT = 5
	};
}
#endif //__UNIVERSUM_LIB_TYPE_GPU_SCHEDULER_COMMAND_TYPE_H