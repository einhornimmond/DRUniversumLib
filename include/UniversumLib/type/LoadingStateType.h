#ifndef __UNIVERSUM_LIB_TYPE_LOADING_STATE_TYPE_H
#define __UNIVERSUM_LIB_TYPE_LOADING_STATE_TYPE_H

namespace UniLib {
	enum class LoadingStateType {
		// empty structure
		EMPTY = 0,
		// has every information needed to load
		HAS_INFORMATIONS = 1,
		// all needed data form storage (hdd/ssd) loaded
		STORAGE_DATA_READY = 3,
		// all data calculated
		CPU_DATA_READY = 5,
		// data on gpu uploaded/generated
		GPU_DATA_READY = 7,
		// fully loaded and ready for using
		FULLY_LOADED = 8
	};
}

#endif //__UNIVERSUM_LIB_TYPE_LOADING_STATE_TYPE_H