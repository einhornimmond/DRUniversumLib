#include "model/Texture.h"
#include "lib/DRIImage.h"

namespace UniLib {
	namespace model {
		Texture::Texture()
			: mImage(NULL), mSize(0), mFormat(0)
		{
		}

		Texture::Texture(DRVector2i size, GLenum format)
			: mImage(NULL), mSize(size), mFormat(format)
		{

		}
		Texture::~Texture()
		{
			clearMemory();
		}

		DHASH Texture::calculateHash(DRVector2i size, GLenum format)
		{
			return size.x | size.y << 16 | (DHASH)(format) << 32;
		}

		DRReturn Texture::loadFromFile(const char* filename)
		{
			if (!mImage) mImage = DRIImage::newImage();
			//std::string completePath = 
			const char* path = DRFileManager::Instance().getWholePfad(filename);
			std::string complete;
			if (path) {
				complete = std::string(path) + std::string("/") + std::string(filename);
			}
			else {
				complete = std::string(filename);
			}

			if (mImage->loadFromFile(complete.data())) {
				DR_SAVE_DELETE(mImage);
				EngineLog.writeToLog("tried to load file: %s", complete.data());
				LOG_ERROR("error by loading texture from storage", DR_ERROR);
			}
			mSize = mImage->getSize();
			mFormat = mImage->getImageFormat();
			return DR_OK;
		}

		DRReturn Texture::loadFromMemory(u8* data)
		{
			if (!mImage) mImage = DRIImage::newImage();
			mImage->setSize(mSize);
			mImage->setImageFormat(-1);
			if (mImage->setPixel(data))
				LOG_ERROR("error setting pixel", DR_ERROR);
			///LOG_INFO("load texture from memory successfully");
			return DR_OK;
		}

		DRReturn Texture::saveIntoFile(const char* filename, u8* data)
		{
			assert(data != NULL);
			assert(filename != NULL);
			if (!mImage) mImage = DRIImage::newImage();
			mImage->setSize(mSize);
			mImage->setImageFormat(-1);
			mImage->setPixel(data);
			return mImage->saveIntoFile(filename);

		}
		DRReturn Texture::saveIntoFile(const char* filename, DRColor* color)
		{
			assert(color != NULL);
			assert(filename != NULL);
			if (!mImage) mImage = DRIImage::newImage();
			mImage->setSize(mSize);
			mImage->setImageFormat(-1);
			mImage->setPixel(color);
			return mImage->saveIntoFile(filename);
		}
		DRReturn Texture::saveIntoFile(const char* filename)
		{
			if (!mImage->getPixel()) LOG_ERROR("no pixels to save", DR_ERROR);
			return mImage->saveIntoFile(filename);
		}

		void Texture::clearMemory()
		{
			if (mImage) {
				DRIImage::deleteImage(mImage);
				mImage = NULL;
			}
		}
	}
}