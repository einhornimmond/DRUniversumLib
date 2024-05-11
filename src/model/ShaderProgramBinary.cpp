#include "UniversumLib/model/ShaderProgramBinary.h"
#include "DRCore2/Foundation/DRFile.h"

namespace UniLib {
	namespace model {
		ShaderProgamBinary::ShaderProgamBinary(const char* fileName)
			: lib::Loadable(LoadingStateType::HAS_INFORMATIONS), mBinaryFormat(0), mFileName(fileName)
		{

		}

		ShaderProgamBinary::~ShaderProgamBinary()
		{

		}

		DRReturn ShaderProgamBinary::load(LoadingStateType target)
		{
			UNIQUE_LOCK;
			auto state = detectLoadingState();
			if (LoadingStateType::HAS_INFORMATIONS == state && LoadingStateType::STORAGE_DATA_READY == target) {
				return loadFromFile();
			}
			return DR_OK;
		}
		
		LoadingStateType ShaderProgamBinary::detectLoadingState()
		{
			UNIQUE_LOCK;
			if (mFileName.empty()) {
				return LoadingStateType::EMPTY;
			}
			if (!mBinaryData.empty()) {
				return LoadingStateType::STORAGE_DATA_READY;
			}
			return LoadingStateType::HAS_INFORMATIONS;
		}

		DRReturn ShaderProgamBinary::loadFromFile()
		{
			DRFile f(mFileName.data(), "rb");
			if (f.isOpen()) {
				size_t binarySize = f.getSize() - sizeof(GLenum);
				if (binarySize > 0) {
					mBinaryData.resize(binarySize, 0);
					f.read(&mBinaryFormat, sizeof(GLenum), 1);
					f.read(mBinaryData.data(), binarySize, 1);
					f.close();
					return DR_OK;
				}
			}
			return DR_ERROR;
		}

		DRReturn ShaderProgamBinary::saveIntoFile()
		{
			DRFile f(mFileName.data(), "wb");
			if (f.isOpen()) {
				f.write(&mBinaryFormat, sizeof(GLenum), 1);
				f.write(mBinaryData.data(), mBinaryData.size(), 1);
				f.close();
			}
			return DR_OK;
		}
	}
}