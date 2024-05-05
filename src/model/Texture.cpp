#include "UniversumLib/model/Texture.h"
#include "UniversumLib/exception/Texture.h"

#include "DRCore2/Manager/DRFileManager.h"
#include "DRCore2/DRCore2Main.h"

#ifdef DEBUG
#define STBI_FAILURE_USERMSG 
#endif
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace UniLib {
	namespace model {
		Texture::Texture()
			: mRawImageData(nullptr), mSize(0), mFormat(0)
		{
		}

		Texture::Texture(const DRVector2i& size, GLenum format)
			: mRawImageData(nullptr), mSize(size), mFormat(format)
		{

		}

		Texture::~Texture()
		{
			clearMemory();
		}

		DHASH Texture::calculateHash(DRVector2i size, GLenum format)
		{
			return size.x | size.y << 16 | (DHASH)(format) << 4;
		}

		DRReturn Texture::loadFromFile(const char* filename)
		{
			const char* path = DRFileManager::Instance().getWholePfad(filename);
			std::string complete;
			if (path) {
				complete = std::string(path) + std::string("/") + std::string(filename);
			}
			else {
				complete = std::string(filename);
			}
			UNIQUE_LOCK;
			if (mRawImageData) free(mRawImageData);
			// channelCount     components
			//       1           grey
			//       2           grey, alpha
			//       3           red, green, blue
			//       4           red, green, blue, alpha
			int channelCount = 0;
			mRawImageData = stbi_load(complete.data(), &mSize.x, &mSize.y, &channelCount, 0);
			if (!mRawImageData) {
				DRLog.writeToLog("tried to load file: %s, message: %s", complete.data(), stbi_failure_reason());
				LOG_ERROR("error by loading texture from storage", DR_ERROR);
			}
			if (4 == channelCount) {
				mFormat = GL_RGBA;
			} else if (3 == channelCount) {
				mFormat = GL_RGB;
			} else {
				DRLog.writeToLog("stb give %d for channel count", channelCount);
				throw exception::LoadTexture("invalid channel count while loading texture with stb", complete.data());
			}
			return DR_OK;
		}

		DRReturn Texture::loadFromMemory(u8* data, const DRVector2i& size, GLenum format)
		{
			UNIQUE_LOCK;
			mSize = size;
			mFormat = format;
			mRawImageData = data;
			return DR_OK;
		}

		DRReturn Texture::saveIntoFile(const char* filename, ImageFileType type)
		{
			UNIQUE_LOCK;
			if (!mRawImageData) {
				LOG_ERROR("no pixels to save", DR_ERROR);
			}
			int result = 0;
			int channelCount = 0;
			if (GL_RGB == mFormat) {
				channelCount = 3;
			}
			else if (GL_RGBA == mFormat) {
				channelCount = 4;
			}
			switch (type) {
			case ImageFileType::PNG: 
				result = stbi_write_png(filename, mSize.x, mSize.y, channelCount, mRawImageData, 0);
				break;
			case ImageFileType::BMP:
				result = stbi_write_bmp(filename, mSize.x, mSize.y, channelCount, mRawImageData);
				break;
			case ImageFileType::TGA:
				result = stbi_write_tga(filename, mSize.x, mSize.y, channelCount, mRawImageData);
				break;
			case ImageFileType::JPG:
				result = stbi_write_jpg(filename, mSize.x, mSize.y, channelCount, mRawImageData, 80);
				break;
			}
			if (result != 0) {
				return DR_OK;
			}
			return DR_ERROR;
		}

		void Texture::clearMemory()
		{
			UNIQUE_LOCK;
			if (mRawImageData) {
				free(mRawImageData);
				mRawImageData = nullptr;
			}
		}
	}
}