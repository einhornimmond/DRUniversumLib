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
#ifndef __DR_UNIVERSUM_TASK_TEXTURE_H__
#define __DR_UNIVERSUM_TASK_TEXTURE_H__

#include "UniversumLib/view/Texture.h"

#include "DRCore2/Threading/DRCPUTask.h"
#include "DRCore2/Threading/DRCPUScheduler.h"

namespace UniLib {
	namespace task {

		/*!
		*
		* \author: Dario Rekowski
		*
		* \date: 03.05.2024
		*
		* \desc: basic for all texure related cpu tasks
		*/
		class Texture : public DRCPUTask
		{
		public:
			Texture(view::Texture* texView, DRCPUScheduler* scheduler)
				: DRCPUTask(scheduler), mViewTexture(texView) {}
			Texture(view::Texture* texView, DRCPUScheduler* scheduler, u8 dependencyCount)
				: DRCPUTask(scheduler, dependencyCount), mViewTexture(texView) {}

			virtual const char* getResourceType() const { return "task::Texture"; };
			inline view::Texture* getViewTexture() { return mViewTexture; }

		protected:
			view::Texture* mViewTexture;


		};
	}
}



#endif //__DR_UNIVERSUM_TASK_TEXTURE_H__