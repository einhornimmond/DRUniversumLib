#ifndef __UNIVERSUM_LIB_TYPE_SECTOR_ID_TYPE_H
#define __UNIVERSUM_LIB_TYPE_SECTOR_ID_TYPE_H

#include "DRCore2/DRTypes.h"

namespace UniLib {
	enum class SectorIdType: u8 {
		DEFAULT = 0,
		BLOCK_SECTOR = 1,
		BLOCK_SECTOR_TREE = 2
	};
}

#endif //__UNIVERSUM_LIB_TYPE_SECTOR_ID_TYPE_H