#include "UniversumLib/model/BlockSector.h"
#include "UniversumLib/view/BlockSector.h"
#include "UniversumLib/model/block/Block.h"
#include "UniversumLib/model/block/BlockType.h"
#include "UniversumLib/model/SectorID.h"

#include "DRCore2/DRCore2Main.h"

namespace UniLib {
	namespace model {

		BlockSector::BlockSector(Node* parent, model::SectorID* id, view::BlockSector* viewSector)
			: Sector(parent, id, dynamic_cast<view::Sector*>(viewSector))
		{
			mType = NodeType::BLOCK_SECTOR;
			memset(mGridSolid, 0, sizeof(u16) * 8 * 8);
		}			//


		BlockSector::~BlockSector()
		{

		}

		DRReturn BlockSector::addBlock(block::BlockPtr block, DRVector3i index)
		{
			assert(index.x >= 0 && index.x < 8);
			assert(index.y >= 0 && index.y < 8);
			assert(index.z >= 0 && index.z < 8);
			HASH h = DRMakeSmallVector3DHash(index);
			if(!isPlaceFree(h)) LOG_ERROR("cannot insert new block, position already occupied!", DR_ERROR);
			mBlocks.insert(BlockPair(h, block));

			auto type = block->getBlockType()->getBaseType();
			assert(magic_enum::enum_integer(type) < 3 && magic_enum::enum_integer(type) >= 0);
			// logging 
			//EngineLog.writeToLog("grid before adding block: %s", getValueAsBinaryString(mGridSolid[index.y][index.z]).data());
			//clear
			mGridSolid[index.y][index.z] &= 0xffff ^ (3 << (index.x * 2));
			// set new value
			mGridSolid[index.y][index.z] |= magic_enum::enum_integer(type) << (index.x * 2);
			//EngineLog.writeToLog("grid after adding this block base type: %d\n%s",
			//	(int)type, getValueAsBinaryString(mGridSolid[index.y][index.z]).data());			

			return DR_OK;
		}

		block::BlockPtr BlockSector::deleteBlock(DRVector3i index)
		{
			HASH h = DRMakeSmallVector3DHash(index);
			if(isPlaceFree(h)) LOG_ERROR("cannot delete block, position is empty", block::BlockPtr());
			BlockIterator it = mBlocks.find(h);
			block::BlockPtr block = it->second;
			mBlocks.erase(it);
			return block;
		}

		block::BlockPtr BlockSector::operator[] (HASH h) const 
		{	
			BlockIterator it = mBlocks.find(h);
			if(it != mBlocks.end()) {
				return it->second;
			} else {
				return block::BlockPtr();
			}
		}


		DRReturn BlockSector::move(float timeSinceLastFrame)
		{
			return DR_OK;
		}
		
	}
}