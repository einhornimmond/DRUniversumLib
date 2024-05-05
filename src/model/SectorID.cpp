#include "UniversumLib/model/SectorID.h"

#include "magic_enum/magic_enum.hpp"

#include <memory>
#include <cassert>

namespace UniLib {
    namespace model {
		
		SectorID::SectorID(u8 id, SectorIdType type, SectorID* parent/* = nullptr*/) : SectorID(&id, 1, type, parent) {}
		SectorID::SectorID(u16 id, SectorIdType type, SectorID* parent/* = nullptr*/) : SectorID((u8*)&id, 2, type, parent) {}
		SectorID::SectorID(u32 id, SectorIdType type, SectorID* parent/* = nullptr*/) : SectorID((u8*)&id, 4, type, parent) {}
		SectorID::SectorID(u64 id, SectorIdType type, SectorID* parent/* = nullptr*/) : SectorID((u8*)&id, 8, type, parent) {}
		SectorID::SectorID(u8* id, u8 arraySize, SectorIdType type, SectorID* parent/* = nullptr*/)
		 : mID(nullptr), mArraySize(arraySize), mType(magic_enum::enum_integer(SectorIdType::DEFAULT)), mParent(parent)
        {
			mID = new u8[arraySize];
			memcpy(mID, id, arraySize);
        }
        SectorID::~SectorID()
        {
			DR_SAVE_DELETE_ARRAY(mID);
        }

		DRReturn SectorID::serialize(u8* buffer) {
			assert(buffer != NULL);
			u8 startIndex = 0;
			if (mParent) {
				startIndex = mParent->getSeralizedSize();
			}
			buffer[startIndex++] = mType;
			buffer[startIndex++] = mArraySize;
			memcpy(&buffer[startIndex], mID, mArraySize);
			if (mParent) {
				return mParent->serialize(buffer);
			}
			return DR_OK;

		}

		int SectorID::getSeralizedSize() 
		{ 
			int size = mArraySize + sizeof(u8)*2;
			if (mParent) size += mParent->getSeralizedSize();
			return size;
		}

		SectorID* SectorID::deserialize(u8* id, u8 arraySize, SectorID* parent/* = NULL*/)
		{
			assert(id != NULL);
			assert(arraySize > 2);
			int currentIndex = 0;
			do {
				u8 type = id[currentIndex++];
				u8 size = id[currentIndex++];
				assert(size <= arraySize - currentIndex);
				parent = new SectorID(&id[currentIndex], size, (SectorIdType)type, parent);
				currentIndex += size;
			} while (currentIndex < arraySize);
			return parent;
		}

		//********************************************************************************************
	
    }
}