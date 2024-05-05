#include "UniversumLib/view/Texture.h"
#include "UniversumLib/exception/Loadable.h"

namespace UniLib {
	namespace view {

		// ********************************************************************
		
		DRReturn TextureGetPixelTask::run()
		{
			return DR_OK;
		}

		DRReturn TextureSavingTask::run()
		{
			model::Texture* m = mViewTexture->getTextureModel();
			if(m->saveIntoFile(mFilename.data())) {
				LOG_ERROR("error saving texture", DR_ERROR);
			}
			if (mHasParent) mViewTexture->setLoadingState(LOADING_STATE_PARTLY_LOADED);
			return DR_OK;
		}

		DRReturn TextureSetPixelTask::run()
		{
			model::Texture* m = mViewTexture->getTextureModel();
			if (m->loadFromMemory(mData)) {
				DR_SAVE_DELETE_ARRAY(mData);
				LOG_ERROR("error setting data", DR_ERROR);
			}
			DR_SAVE_DELETE_ARRAY(mData);
			if(!mHasParent)
				mViewTexture->setLoadingState(LOADING_STATE_PARTLY_LOADED);
			if (mFinishCommand) mFinishCommand->taskFinished(this);
			return DR_OK;
		}
		// ********************************************************************


		Texture::Texture(DHASH id, const char* textureName/* = NULL*/)
			: mTextureModel(NULL), mId(id)
		{
			if (textureName) {
				mTextureName = textureName;
				setLoadingState(LoadingStateType::HAS_INFORMATIONS);
			}
		}

		Texture::Texture(DRVector2i size, GLenum format)
			: mTextureModel(new model::Texture(size, format))
		{
			mId = mTextureModel->getHash();
			setLoadingState(LoadingStateType::HAS_INFORMATIONS);
		}

		Texture::~Texture()
		{
		}

		void Texture::saveIntoFile(const char* filename)
		{
			// TODO: check if pixel exist (in system memory) if not first copy pixel
			controller::TaskPtr task(new TextureSavingTask(this, controller::TextureManager::getInstance()->getTextureCPUScheduler(), filename));
			task->scheduleTask(task);
		}

		

		DRReturn Texture::loadFromMemory(u8* data, controller::Command* finishCommand)
		{
			if (!mTextureModel) 
				LOG_ERROR("texture model not created, size not known!", DR_ERROR);
			controller::TaskPtr task(new TextureSetPixelTask(this, controller::TextureManager::getInstance()->getTextureCPUScheduler(), data));
			if (finishCommand) task->setFinishCommand(finishCommand);
			task->scheduleTask(task);
			
			return DR_OK;
		}
		DRReturn Texture::saveIntoFile(const char* filename, u8* data)
		{
			if (!mTextureModel)
				LOG_ERROR("texture model not created, size not known!", DR_ERROR);
			controller::CPUSheduler* textureScheduler = controller::TextureManager::getInstance()->getTextureCPUScheduler();
			TextureSetPixelTask* setPixel = new TextureSetPixelTask(this, textureScheduler, data);
			setPixel->hasParent();
			controller::TaskPtr setPixelTask(setPixel);
			TextureSavingTask* savingTask = new TextureSavingTask(this, textureScheduler, filename, 1);
			controller::TaskPtr savingTaskPtr(savingTask);
			savingTaskPtr->setParentTaskPtrInArray(setPixelTask, 0);
			mTextureName = filename;
#ifdef _UNI_LIB_DEBUG
			setPixel->setName(filename);
			savingTask->setName(filename);
#endif
			savingTaskPtr->scheduleTask(savingTaskPtr);
			return DR_OK;
		}

		LoadingStateType Texture::detectLoadingState()
		{
			if (uploadedToGPU()) {
				return LoadingStateType::FULLY_LOADED;
			}
			if (mTextureModel && mTextureModel->hasImageData()) {
				return LoadingStateType::CPU_DATA_READY;
			}
			if (!mTextureModel && mTextureName.empty()) {
				return LoadingStateType::EMPTY;
			}

			return LoadingStateType::HAS_INFORMATIONS;
			
		}

		DRReturn Texture::load(LoadingStateType target)
		{
			auto state = checkLoadingState();
			if (target == LoadingStateType::STORAGE_DATA_READY || target == LoadingStateType::CPU_DATA_READY)
			{
				if (state != LoadingStateType::HAS_INFORMATIONS) {
					throw exception::LoadableInvalidLoadOrder("wrong loading state for loading texture from storage", state, target);
				}
				return mTextureModel->loadFromFile(mTextureName.data());
			}
			if (target == LoadingStateType::GPU_DATA_READY) {
				if (state != LoadingStateType::CPU_DATA_READY) {
					throw exception::LoadableInvalidLoadOrder("wrong loading state for upload texture to gpu", state, target);
				}
				uploadToGPU();
				return DR_OK;
			}
			return DR_ERROR;
		}
	}
}