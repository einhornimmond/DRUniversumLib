#include "Core2Main.h"

#define VIRTUAL_FILE_VERSION 1


using namespace DRFilePart;

DRVirtualCustomFile::~DRVirtualCustomFile()
{
	if (mFreeMemory) {
		for (FilePartListIterator it = mFileParts.begin(); it != mFileParts.end(); it++) {
			DR_SAVE_DELETE(*it);
		}
	}
	mFileParts.clear();
}

void DRVirtualCustomFile::write(FilePart* part)
{
	mFileParts.push_back(part);
}

FilePart* DRVirtualCustomFile::read()
{
	FilePart* result = mFileParts.front();
	mFileParts.pop_front();
	return result;
}

DRReturn DRVirtualCustomFile::saveToFile(const char* filename)
{
	DRFile file(filename, "wb");
	if (file.isOpen()) {
		const char start[] = VIRTUAL_FILE_HEAD;
		const s32 fileVersion = VIRTUAL_FILE_VERSION;
		file.write(start, 1, 10);
		file.write(&fileVersion, sizeof(s32), 1);
		for (FilePartListIterator it = mFileParts.begin(); it != mFileParts.end(); it++) {
			Type type = (*it)->type();
			size_t size = (*it)->size();
			size_t count = (*it)->count();
			file.write(&type, sizeof(Type), 1);
			file.write(&size, sizeof(size_t), 1);
			file.write(&count, sizeof(size_t), 1);
			file.write((*it)->data(), size, count);
		}
		return DR_OK;
	}
	DRLog.writeToLog("%s couldn't be created", filename);
	LOG_ERROR("Error create file", DR_ERROR);
}
DRReturn DRVirtualCustomFile::readFromFile(const char* filename)
{
	DRFile file(filename, "rb");
	if (file.isOpen()) {
		char start[10];
		s32 fileVersion = 0;
		u32 fileSize = file.getSize();
		if (fileSize < 14) LOG_ERROR("file to small", DR_ERROR);
		file.read(start, 1, 10);
		file.read(&fileVersion, sizeof(s32), 1);
		if (strcmp(start, VIRTUAL_FILE_HEAD) != 0) LOG_ERROR("head string didn't match", DR_ERROR);
		if (fileVersion != VIRTUAL_FILE_VERSION) LOG_ERROR("file version didn't match", DR_ERROR);
		while (fileSize > file.getFilePointer()) {
			Type type = FILE_PART_UNKNOWN;
			size_t size = 0;
			size_t count = 0;
			file.read(&type, sizeof(Type), 1);
			file.read(&size, sizeof(size_t), 1);
			file.read(&count, sizeof(size_t), 1);
			void* bin = (void*)malloc(size*count);
			file.read(bin, size, count);

			FilePart* fp = NULL;
			switch (type) {
			case FILE_PART_INT: fp = new Integer(*(s32*)bin); free(bin); break;
			case FILE_PART_FLOAT: fp = new Float(*(float*)bin); free(bin); break;
			case FILE_PART_SHORT: fp = new Short(*(s16*)bin); free(bin); break;
			case FILE_PART_BYTE: fp = new Byte(*(u8*)bin); free(bin); break;
			case FILE_PART_BIN: fp = new Binary(bin, size); break;
			case FILE_PART_ARRAY_FLOAT: fp = new FloatArray((float*)bin, count, true, true); free(bin); break;
			case FILE_PART_ARRAY_INT: fp = new IntegerArray((s32*)bin, count, true, true); free(bin); break;
			default: free(bin);
			}
			if (fp) mFileParts.push_back(fp);
		}
		return DR_OK;
	}
	DRLog.writeToLog("%s file not found", filename);
	LOG_ERROR("Error open file", DR_ERROR);
}

// ********************************************************************
// Virtual Binary File
// ********************************************************************
DRReturn DRVirtualBinaryFile::readFromFile(const char* filename)
{
	DRFile file(filename, "rb");
	if (file.isOpen()) {
		mBinSize = file.getSize();
		mBinData = (void*)malloc(mBinSize);
		file.read(mBinData, mBinSize, 1);
		file.close();
		return DR_OK;
	}
	DRLog.writeToLog("%s not found", filename);
	LOG_ERROR("error opening file", DR_ERROR);
}

DRReturn DRVirtualBinaryFile::saveToFile(const char* filename)
{
	DRFile file(filename, "wb");
	if (file.isOpen()) {
		file.write(mBinData, mBinSize, 1);
		file.close();
		return DR_OK;
	}
	DRLog.writeToLog("couldn't create or open %s", filename);
	LOG_ERROR("error writing into file", DR_ERROR);
}
