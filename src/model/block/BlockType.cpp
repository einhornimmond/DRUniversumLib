#include "UniversumLib/model/block/BlockType.h"
#include <sstream>

namespace UniLib {
	namespace model {
		namespace block {

			BlockType::BlockType(std::string name)
				: mId(0), mName(name), mBaseType(BLOCK_BASE_TYPE_NONE), mTransparency(false),
				  mDensity(0.0f), mMeltingPoint(0.0f), mHitpoints(0)
			{

			}

			BlockType::~BlockType()
			{

			}

			BlockBaseType BlockType::getBlockBaseTypeEnum(std::string blockBaseTypeString)
			{
				if(blockBaseTypeString == std::string("solid")) return BLOCK_BASE_TYPE_SOLID;
				if(blockBaseTypeString == std::string("fluent")) return BLOCK_BASE_TYPE_FLUENT;
				if(blockBaseTypeString == std::string("gas")) return BLOCK_BASE_TYPE_GAS;
				return BLOCK_BASE_TYPE_SOLID;
			}

			std::string BlockType::asString()
			{
				std::stringstream s;
				s << "Name: " << mName << std::endl;
				s << "Base Type: " << mBaseType << std::endl;
				s << "Transparency: " << mTransparency << std::endl;
				s << "Density: " << mDensity << std::endl;
				s << "Melting point: " << mMeltingPoint << std::endl;
				s << "Hitpoints: " << mHitpoints << std::endl;

				return s.str();
			}
		}
	}
}