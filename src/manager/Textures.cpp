#include "UniversumLib/manager/Textures.h"
#include "UniversumLib/controller/BindToRenderer.h"
#include "UniversumLib/model/Texture.h"
#include "UniversumLib/view/Texture.h"

#include "DRCore2/DRCore2Main.h"
#include "DRCore2/Foundation/DRHash.h"

namespace UniLib {
	namespace manager {

		Textures::Textures()
			: mInitalized(false), mTimer(nullptr)
		{

		}

		Textures::Textures(const Textures&)
			: mInitalized(false), mTimer(nullptr)
		{

		}

		Textures* const Textures::getInstance()
		{
			static Textures TheOneAndOnly;
			return &TheOneAndOnly;
		}

		DRReturn Textures::init(DRFuzzyTimer* updateTimer, std::chrono::duration<u64, std::milli> rerunDelay/* = 10000ms*/)
		{
			// wait 20 seconds before deleting not used textures, maybe some other thread need the memory
			mTimeToLetEmptyTexturesInStorage = 20s;
			updateTimer->addTimer(TEXTURE_MANAGER_TIMER_NAME, this, rerunDelay);
			mTimer = updateTimer;
			
			mInitalized = true;
			LOG_INFO("TextureManager initalisiert");
			return DR_OK;
		}

		void Textures::exit()
		{
			mInitalized = false;
			if (mTimer) {
				mTimer->removeTimer(TEXTURE_MANAGER_TIMER_NAME);
			}
			LOG_INFO("TextureManager beendet");
		}

		view::TexturePtr Textures::getTexture(const char* filename)
		{
			assert(g_RenderBinder != NULL);

			DHASH id = DRMakeFilenameHash(filename); 
			UNIQUE_LOCK;
			TextureMap::iterator it = mStoredTextures.find(id);
			if (it != mStoredTextures.end()) {
				return it->second;
			}
			view::TexturePtr tex = view::TexturePtr(g_RenderBinder->newTexture(id, filename));
			tex->asyncLoad(LoadingStateType::STORAGE_DATA_READY);
			mStoredTextures.insert(TextureEntry(id, tex));
			return tex;
		}

		view::TexturePtr Textures::getEmptyTexture(DRVector2i size, GLenum format)
		{
			assert(g_RenderBinder != NULL);

			DHASH id = model::Texture::calculateHash(size, format);
			UNIQUE_LOCK;
			TextureMultiMap::iterator it = mEmptyTextures.find(id);
			if (it != mEmptyTextures.end()) {
				view::TexturePtr tex = it->second.texture;
				mEmptyTextures.erase(it);
				return tex;
			}
			view::TexturePtr tex = view::TexturePtr(g_RenderBinder->newTexture(size, format));
			tex->asyncLoad(LoadingStateType::GPU_DATA_READY);
			return tex;
		}

		void Textures::giveBackEmptyTexture(view::TexturePtr tex)
		{
			DHASH id = tex->getId();
			UNIQUE_LOCK;
			EmptyTexture empty;
			empty.texture = tex;
			empty.timeout = std::chrono::steady_clock::now() + mTimeToLetEmptyTexturesInStorage;
			mEmptyTextures.insert(EmptyTextureEntry(id, empty));
		}

		TimerReturn Textures::callFromTimer()
		{
			if (!mInitalized) return TimerReturn::REMOVE_ME;
			UNIQUE_LOCK;
			auto now = std::chrono::steady_clock::now();
			// check multimap timeout
			for (TextureMultiMap::iterator it = mEmptyTextures.begin(); it != mEmptyTextures.end(); it++) {
				// enough time has passed, we remove texture storage from memory
				if (now > it->second.timeout) {
					it = mEmptyTextures.erase(it);
				}
			}
			// check map and removing not longer used textures
			for (TextureMap::iterator it = mStoredTextures.begin(); it != mStoredTextures.end(); it++) {
				view::TexturePtr tex = it->second;
				if (tex.use_count() == 1) {
					giveBackEmptyTexture(tex);
					it = mStoredTextures.erase(it);
				}
			}
			return TimerReturn::GO_ON;
		}
	}
}