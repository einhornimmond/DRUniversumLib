#include "UniversumLib/model/UniformSet.h"

#include "DRCore2/Foundation/DRHash.h"

#include <cassert>

namespace UniLib
{
	namespace model {
		
        UniformSet::UniformSet()
			:mDirtyFlag(false)
        {
        }
        // -------------------------------------------------------------------
        UniformSet::~UniformSet()
        {
            for(std::map<HASH, UniformEntry*>::iterator it = mUniformEntrys.begin(); it != mUniformEntrys.end(); it++) {
                delete it->second;
            }
            mUniformEntrys.clear();
        }
		// inlined
		/*
        DRReturn UniformSet::setUniform(const char* name, int value)
        {
            return setUniform(&value, 1, name, false);
        }
        DRReturn UniformSet::setUniform(const char* name, float value)
        {
            return setUniform(&value, 1, name, true);
        }
        DRReturn UniformSet::setUniform(const char* name, DRVector2 value)
        {
            return setUniform(value.c, 2, name, true);
        }
        DRReturn UniformSet::setUniform(const char* name, DRVector3 value)
        {
            return setUniform(value.c, 3, name, true);
        }
        DRReturn UniformSet::setUniform(const char* name, DRColor value)
        {
            return setUniform(value.c, 4, name, true);
        }
        DRReturn UniformSet::setUniform(const char* name, DRVector3i value)
        {
            return setUniform(value.c, 3, name, false);
        }
        DRReturn UniformSet::setUniform(const char* name, DRVector2i value)
        {
            return setUniform(value.c, 2, name, false);
        }
		DRReturn UniformSet::setUniform(const char* name, DRMatrix value)
		{
			return setUniform(value.n, 16, name, true);
		}
		*/
		DRMatrix UniformSet::getUniformMatrix(const char* name)
		{
			UNIQUE_LOCK;
			return (float*)getUniform(name, 16);
		}

		DRReturn UniformSet::addUniformMapping(const char* name, void* location, HASH programID)
		{
			UNIQUE_LOCK;
			UniformEntry* entry = getUniformEntry(name);
			if(entry) {
				entry->addLocation(location, programID);
				return DR_OK;
			}
			return DR_ERROR;
		}
		DRReturn UniformSet::removeUniformMapping(const char* name, HASH programID)
		{
			UNIQUE_LOCK;
			UniformEntry* entry = getUniformEntry(name);
			if(entry) {
				entry->removeLocation(programID);
				return DR_OK;
			}
			return DR_ERROR;
		}
		void UniformSet::updateDirtyFlags()
		{
			UNIQUE_LOCK;
			if(!mDirtyFlag) {
				return;
			}
			for(std::map<HASH, UniformEntry*>::iterator it = mUniformEntrys.begin(); it != mUniformEntrys.end(); it++) {
				it->second->checkDirty();
				if(it->second->isDirty()) { 
					return;
				}
			}
			mDirtyFlag = false;
		}
        // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // PROTECTED AREA
        // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        UniformSet::UniformEntry::UniformEntry(int* data, size_t arrayEntryCount, const char* name)
            : type(arrayEntryCount + 64), intArray(NULL), name(name)
        {
			assert(arrayEntryCount < 64);
            intArray = new int[arrayEntryCount];
            memcpy(intArray, data, arrayEntryCount*sizeof(int));
        }
        UniformSet::UniformEntry::UniformEntry(float* data, size_t arrayEntryCount, const char* name)
            : type(arrayEntryCount + 64), floatArray(NULL), name(name)
        {
			assert(arrayEntryCount < 64);
			type |= 128;
            floatArray = new float[arrayEntryCount];
            memcpy(floatArray, data, arrayEntryCount*sizeof(float));
        }
        UniformSet::UniformEntry::~UniformEntry()
        {
           DR_SAVE_DELETE_ARRAY(intArray);
		   type = 0;
        }

        DRReturn UniformSet::UniformEntry::update(void* data, size_t arrayEntryCount, const char* name)
        {
			assert(arrayEntryCount == (type & 63));
			if((type & 128) == 128) {
				memcpy(floatArray, data, arrayEntryCount*sizeof(float));
			} else {
				memcpy(intArray, data, arrayEntryCount*sizeof(int));
			}
			setDirty();
			for(std::map<HASH, Location>::iterator it = locations.begin(); it != locations.end(); it++) {
				it->second.dirty = true;
			}
            return DR_OK;
        }
		void UniformSet::UniformEntry::addLocation(void* location, HASH programID)
		{
			//locations.push_back(location);
			locations.insert(LOCATION_PAIR(programID, Location(location)));
		}
		void UniformSet::UniformEntry::removeLocation(HASH programID)
		{
			locations.erase(programID);
		}
		void UniformSet::UniformEntry::checkDirty()
		{
			if(!isDirty()) return;
			for(std::map<HASH, Location>::iterator it = locations.begin(); it != locations.end(); it++) {
				if(it->second.dirty) return;
			}
			unsetDirty();
		}
        // ******************************************************************
		DRReturn UniformSet::setUniform(void* data, size_t arrayEntryCount, const char* name, bool typeFloat/* = false*/)
        //DRReturn UniformSet::setUniform(UniformEntry* newUniform)
        {
            if(!data) return DR_ZERO_POINTER;
			UNIQUE_LOCK;
			mDirtyFlag = true;
			UniformEntry* entry = getUniformEntry(name);
            if(entry) {
                DRReturn result = entry->update(data, arrayEntryCount, name);
                return result;
            } else {
				HASH hash = DRMakeStringHash(name);
				if(typeFloat) entry = new UniformEntry((float*)data, arrayEntryCount, name);
				else entry = new UniformEntry((int*)data, arrayEntryCount, name);
                mUniformEntrys.insert(UNIFORM_ENTRY_PAIR(hash, entry));
            }
            return DR_OK;
        }

		void* UniformSet::getUniform(const char* name, size_t arrayEntryCount)
		{
			UniformEntry* entry = getUniformEntry(name);
			if(entry) {
				assert(entry->getArraySize() == arrayEntryCount);
				return entry->intArray;
			} 
			return NULL;
		}

		UniformSet::UniformEntry* UniformSet::getUniformEntry(const char* name)
		{
			HASH hash = DRMakeStringHash(name);
			std::map<HASH, UniformEntry*>::iterator it = mUniformEntrys.find(hash);
			if(it != mUniformEntrys.end()) {
				return it->second;
			}
			return NULL;
		}

	};
};