/*/*************************************************************************
*                                                                         *
* UniversumLib, collection of classes for generating and go through a     *
* whole universe. It is for my Gameproject Spacecraft					   *
* Copyright (C) 2014, 2015, 2016, 2017 Dario Rekowski.					   *
* Email: dario.rekowski@gmx.de   Web: www.spacecrafting.de                *
*                                                                         *
* This program is free software: you can redistribute it and/or modify    *
* it under the terms of the GNU General Public License as published by    *
* the Free Software Foundation, either version 3 of the License, or       *
* any later version.													   *
*																		   *
* This program is distributed in the hope that it will be useful,	       *
* but WITHOUT ANY WARRANTY; without even the implied warranty of	       *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	       *
* GNU General Public License for more details.							   *
*																		   *
* You should have received a copy of the GNU General Public License	   *
* along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
*                                                                         *
***************************************************************************/

/*!
 *
 * \author: Dario Rekowski 
 *
 * \date: 06.03.2016
 * 
 * \desc: Singleton Texture Manager for efficiency texture managing
 *        loading and saving by using the best suited scheduler
 *		  stores empty texture buffer for reusing
 */

#ifndef __DR_UNIVERSUM_LIN_CONTROLLER_TEXTURE_MANAGER_H
#define __DR_UNIVERSUM_LIN_CONTROLLER_TEXTURE_MANAGER_H

#include "UniversumLib/UniversumLib.h"
#include "UniversumLib/view/Texture.h"
#include "DRCore2/DRTypes.h"
#include "DRCore2/Foundation/DRVector2i.h"
#include "DRCore2/Threading/DRFuzzyTimer.h"
#include "DRCore2/Threading/DRMultithreadContainer.h"

#include <memory>
#include <map>

using namespace std::chrono_literals;
#define TEXTURE_MANAGER_TIMER_NAME "TextureManager"

namespace UniLib {

	namespace manager {
		class UNIVERSUMLIB_EXPORT Textures: public DRTimerCallback, private DRMultithreadContainer
		{
		public:
			static Textures* const getInstance();
			inline static bool	isInitialized() { return getInstance()->mInitalized; };

			//! \brief init 
			//! \param updateTimer timer on which to attach for updating texture storage
			//! \param rerunDelay how much ms passes between update calls
			DRReturn init(DRFuzzyTimer* updateTimer, std::chrono::duration<u64, std::milli> rerunDelay = 10000ms);
			void exit();

			view::TexturePtr getTexture(const char* filename);
	
			//!	\param size 
			//!	\param format allowed values: 
			//!		GL_RED, GL_RG, GL_RGB, GL_BGR, GL_RGBA,
			//!     GL_BGRA, GL_RED_INTEGER, GL_RG_INTEGER,
			//!     GL_RGB_INTEGER, GL_BGR_INTEGER, GL_RGBA_INTEGER,
			//!     GL_BGRA_INTEGER, GL_STENCIL_INDEX, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL
			view::TexturePtr getEmptyTexture(DRVector2i size, GLenum format);
			void giveBackEmptyTexture(view::TexturePtr tex);

			// access
			inline void setTimeoutForNotLongerUsedTextures(std::chrono::duration<u32, std::milli> timeout) { mTimeToLetEmptyTexturesInStorage = timeout; }

			const char* getTimerCallbackType() const { return "TextureManager"; };
			// used to cleanup space for not longer used texture after timeout,
			// called from fuzzy timmer
			TimerReturn callFromTimer();

		protected:
			Textures();
			Textures(const Textures&);
			virtual ~Textures() { if (mInitalized) exit(); };

			// member variables
			bool mInitalized;
			DRFuzzyTimer* mTimer;

			std::chrono::duration<u32, std::milli> mTimeToLetEmptyTexturesInStorage;

			struct EmptyTexture {
				view::TexturePtr texture;
				std::chrono::time_point<std::chrono::steady_clock> timeout;
			};

			// store existing textures
			typedef std::pair<DHASH, view::TexturePtr> TextureEntry;
			typedef std::map<DHASH, view::TexturePtr> TextureMap;
			typedef std::pair<DHASH, EmptyTexture> EmptyTextureEntry;
			typedef std::multimap<DHASH, EmptyTexture> TextureMultiMap;
			TextureMap mStoredTextures;
			TextureMultiMap mEmptyTextures;
		};
	}
}

#endif