#ifndef __UNIVERSUM_LIB_TYPE_NODE_TYPE_H
#define __UNIVERSUM_LIB_TYPE_NODE_TYPE_H

namespace UniLib {

	// node type
	enum class NodeType {
		NONE = 0,
		NODE = 1,
		MOVEABLE = 2,
		VISIBLE = 4,
		SECTOR = 8,
		BLOCK_SECTOR = 16,
		OCTREE = 32,
		BLOCK_SECTOR_TREE = 64
	};
}

#endif //__UNIVERSUM_LIB_TYPE_NODE_TYPE_H