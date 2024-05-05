#include "UniversumLib/controller/InputControls.h"
#include "UniversumLib/controller/InputCommand.h"

#include "SDL_events.h"

#include <cassert>

namespace UniLib {
	namespace controller {

		InputControls* InputControls::mpInstanz = nullptr;

		InputControls::InputControls()
			: mMouseMoveBuffer(0), mLastKeyStates(nullptr), mLastKeyStatesSize(0)
		{
		}

		InputControls::~InputControls()
		{
		}

		InputControls* InputControls::getInstance()
		{
			// Die Instanz wird erst beim ersten Aufruf erzeugt.
			if (!mpInstanz)
				mpInstanz = new InputControls;
			return (InputControls*)mpInstanz;
		}

		bool InputControls::isKeyPressed(SDL_Keycode whichKey) 
		{
			int keyCount = 0;
			std::unique_lock _lock(mWorkMutex);
			assert(whichKey > 0 && whichKey < mLastKeyStatesSize);
			return mLastKeyStates[whichKey] == 1;
		}
		bool InputControls::isKeyPressed(InputCommandType whichKey)
		{
			return isKeyPressed(getKeyCodeForCommand(whichKey));
		}
		
		void InputControls::setMapping(SDL_Keycode sdlKeycode, InputCommandType command)
		{
			CommandMappingIterator it = mCommandMapping.find(command);
			if(it != mCommandMapping.end()) {
				it->second = sdlKeycode;
			} else {
				mCommandMapping.insert(CommandMappingPair(command, sdlKeycode));
			}
			KeycodeMappingIterator it2 = mKeycodeMapping.find(sdlKeycode);
			if(it2 != mKeycodeMapping.end()) {
				it2->second = command;
			} else {
				mKeycodeMapping.insert(KeycodeMappingPair(sdlKeycode, command));
			}
		}
		
		SDL_Keycode InputControls::getKeyCodeForCommand(InputCommandType command)
		{
			CommandMappingIterator it = mCommandMapping.find(command);
			if(it != mCommandMapping.end()) {
				return it->second;
			} 
			return SDLK_UNKNOWN;
		}
		

		InputCommandType InputControls::getCommandForKeycode(SDL_Keycode sdlKeycode)
		{
			KeycodeMappingIterator it = mKeycodeMapping.find(sdlKeycode);
			if(it != mKeycodeMapping.end()) {
				return it->second;
			} 
			return InputCommandType::UNKNOWN;
		}
		
		void InputControls::addingInputCommand(InputCommand* cmd)
		{
			mInputCommands.push_back(cmd);
		}
		void InputControls::removeInputCommand(InputCommand* cmd)
		{
			for(std::list<InputCommand*>::iterator it = mInputCommands.begin(); it != mInputCommands.end(); it++) {
				if(cmd == *it) it = mInputCommands.erase(it);
			}
		}
		DRReturn InputControls::inputLoop()
		{
			SDL_Event event;
			SDL_GetRelativeMouseState(&mMouseMoveBuffer.x, &mMouseMoveBuffer.y);

			/* Poll for events */
			while( SDL_PollEvent( &event ) ){
				InputCommandType in = getCommandForKeycode(event.type);
				if(in != InputCommandType::UNKNOWN) {
					for(std::list<InputCommand*>::iterator it = mInputCommands.begin(); it != mInputCommands.end(); it++) 
					{
						if((*it)->input(in)) it = mInputCommands.erase(it);
					}
				}				
			}
			// copy current keyboard key state for access from other threads
			int keyCount = 0;
			const Uint8 *keys = SDL_GetKeyboardState(&keyCount);
			std::unique_lock _lock(mWorkMutex);
			if(keyCount != mLastKeyStatesSize) {
				mLastKeyStatesSize = keyCount;
				DR_SAVE_DELETE_ARRAY(mLastKeyStates);
				mLastKeyStates = new Uint8[mLastKeyStatesSize];
			}
			memcpy(mLastKeyStates, keys, sizeof(Uint8)* keyCount);
			return DR_OK;
		}
	}
}



