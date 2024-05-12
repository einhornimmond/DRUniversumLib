#include "UniversumLib/model/block/BlockType.h"
#include <sstream>

#include "magic_enum/magic_enum_iostream.hpp"

using magic_enum::iostream_operators::operator<<;

namespace UniLib {
	namespace model {
		namespace block {

			BlockType::BlockType(std::string name)
				: mId(0), mName(name), mBaseType(BlockAggregateType::NONE), mTransparency(false),
				  mDensity(0.0f), mMeltingPoint(0.0f), mHitpoints(0)
			{

			}

			BlockType::~BlockType()
			{

			}

			std::string BlockType::toString()
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