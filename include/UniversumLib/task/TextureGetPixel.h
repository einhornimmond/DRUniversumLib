/*/*************************************************************************
*                                                                         *
* UniversumLib, collection of classes for generating and go through a     *
* whole universe. It is for my Gameproject Spacecraft					   *
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
#ifndef __DR_UNIVERSUM_TASK_TEXTURE_GET_PIXEL_H__
#define __DR_UNIVERSUM_TASK_TEXTURE_GET_PIXEL_H__

#include "Texture.h"

#include "UniversumLib/view/Texture.h"

#include "DRCore2/Threading/DRCPUTask.h"

namespace UniLib {
	namespace task {

		/*!
		*
		* \author: Dario Rekowski
		*
		* \date: 03.05.2024
		*
		* \desc: task get pixel in texture
		*/
		class TextureGetPixel : public Texture
		{
		public:
			TextureGetPixel(view::Texture* texView, DRCPUScheduler* scheduler)
				: Texture(texView, scheduler) {}
			virtual DRReturn run();
			virtual const char* getResourceType() const { return "task::TextureGetPixel"; };
		};
	}
}

#endif //__DR_UNIVERSUM_TASK_TEXTURE_GET_PIXEL_H__
