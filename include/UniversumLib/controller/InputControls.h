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
 * \author Dario Rekowski
 * 
 * \date 25.10.2015
 * 
 * \desc InputControls Singleton, Input Control Hub
 */

#ifndef _DR_UNIVERSUM_LIB_CONTROLLER_INPUT_CONTROLS_H_
#define _DR_UNIVERSUM_LIB_CONTROLLER_INPUT_CONTROLS_H_

#include "InputCommand.h"

#include "DRCore2/Foundation/DRVector2.h"
#include "DRCore2/DRTypes.h"

#include "SDL_keycode.h"

#include <map>
#include <list>
#include <mutex>

namespace UniLib {
	namespace controller {

		class UNIVERSUMLIB_EXPORT InputControls
		{
		public:
			// return the one and one instance (create if not exist)
			static InputControls* getInstance();

			// \return true if key is currently pressed
			bool isKeyPressed(SDL_Keycode whichKey);
			// \return true if key is currently pressed
			bool isKeyPressed(InputCommandType whichKey);

			void addingInputCommand(InputCommand* cmd);
			void removeInputCommand(InputCommand* cmd);

			// set key command mapping
			void setMapping(SDL_Keycode sdlKeycode, InputCommandType command);

			SDL_Keycode getKeyCodeForCommand(InputCommandType command);
			InputCommandType getCommandForKeycode(SDL_Keycode sdlKeycode);

			// update event queue, must be called every frame from main thread (SDL init thread)
			DRReturn inputLoop();

			// \return return mouse move since last frame
			inline DRVector2i getRelativeMousePos() {return mMouseMoveBuffer;}



		protected:
			InputControls();
			virtual ~InputControls();

			// command type key code mapping
			typedef std::pair<InputCommandType, SDL_Keycode> CommandMappingPair;
			typedef std::map<InputCommandType, SDL_Keycode>::iterator CommandMappingIterator;
			std::map<InputCommandType, SDL_Keycode> mCommandMapping;

			// key code command mapping
			typedef std::pair<SDL_Keycode, InputCommandType> KeycodeMappingPair;
			typedef std::map<SDL_Keycode, InputCommandType>::iterator KeycodeMappingIterator;
			std::map<SDL_Keycode, InputCommandType> mKeycodeMapping;

			std::list<InputCommand*> mInputCommands;
			DRVector2i mMouseMoveBuffer;

			// thread save
			std::mutex mWorkMutex;
			u8*     mLastKeyStates;
			int		   mLastKeyStatesSize;

		private:
			static InputControls* mpInstanz;
		};
	}
}

#endif //_DR_UNIVERSUM_LIB_CONTROLLER_INPUT_CONTROLS_H_