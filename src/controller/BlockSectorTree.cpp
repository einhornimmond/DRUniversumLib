#include "UniversumLib/controller/BlockSectorTree.h"
#include "UniversumLib/controller/BindToRenderer.h"
#include "UniversumLib/model/BlockSector.h"
#include "UniversumLib/model/SectorID.h"
#include "UniversumLib/type/NodeType.h"
#include "UniversumLib/type/SectorIdType.h"

#include "DRCore2/DRCore2Main.h"

#include "magic_enum/magic_enum.hpp"

namespace UniLib {
	namespace controller {
		BlockSectorTree::BlockSectorTree(model::SectorID* id, model::Node* parent)
			: OctreeNode(id, parent)
		{
			mType |= NodeType::BLOCK_SECTOR_TREE;
		}

		BlockSectorTree::~BlockSectorTree()
		{

		}

		DRReturn BlockSectorTree::move(float timeSinceLastFrame)
		{
			return OctreeNode::move(timeSinceLastFrame);
			//return DR_OK;
		}

		DRReturn BlockSectorTree::addBlock(model::block::BlockPtr block, std::queue<u8> path, DRVector3i pos)
		{
			assert(!path.empty());
			u8 index = path.front();
			path.pop();
			model::Node* node = mChilds[index];
			// we have no node on this place, we must create it
			if (!node) {
				if (!path.empty()) {
					model::SectorID* id = new model::SectorID(index, SectorIdType::BLOCK_SECTOR_TREE);
					id->setParent(mID);
					BlockSectorTree* n = new BlockSectorTree(id, this);
					mChilds[index] = n;
					return n->addBlock(block, path, pos);
				}
				else {
					model::SectorID* id = new model::SectorID(index, SectorIdType::BLOCK_SECTOR);
					id->setParent(mID);
					model::BlockSector* b = new model::BlockSector(this, id, g_RenderBinder->newBlockSector());
					mChilds[index] = b;
					return b->addBlock(block, pos);
				}
			}
			// the leaf is not yet reached
			else if (node->isTypeOf(mType) ) {
				BlockSectorTree* n = static_cast<BlockSectorTree*>(node);
				if (!path.empty()) {
					return n->addBlock(block, path, pos);
				}
			}
			// we actually have the leaf node
			else if (node->isTypeOf(NodeType::BLOCK_SECTOR)) {
				model::BlockSector* b = static_cast<model::BlockSector*>(node);
				return b->addBlock(block, pos);
			}
			else {
				LOG_ERROR("node has wrong type", DR_ERROR);
			}
			LOG_ERROR("didn't found valid path", DR_ERROR);
		}
	}
}