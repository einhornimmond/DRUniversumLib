#include "UniversumLib/model/block/Block.h"
#include "UniversumLib/model/block/BlockType.h"
#include "UniversumLib/manager/BlockTypes.h"

namespace UniLib {
	namespace model {
		namespace block {
			Block::Block(HASH blockTypeId)
				: mTypeData(NULL)
			{
				mTypeData = manager::BlockTypes::getInstance()->getBlockType(blockTypeId);
			}

			Block::Block(const char* name)
				: mTypeData(NULL)
			{
				mTypeData = manager::BlockTypes::getInstance()->getBlockType(name);
			}


			Block::~Block()
			{

			}
		}
	}
}