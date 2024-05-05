#include "UniversumLib/controller/InputCamera.h"
#include "UniversumLib/controller/InputControls.h"
#include "UniversumLib/task/gpu/Scheduler.h"

#include "SDL_keyboard.h"

namespace UniLib {
	namespace controller {

		InputCamera::InputCamera(float mvSpeed, float rotateSpeed, float fov)
			: Camera(fov), mMoveSpeed(mvSpeed), mRotationSpeed(rotateSpeed)
		{
			//InputControls::getInstance()->addingInputCommand(this);
		}

		InputCamera::~InputCamera()
		{

		}

		void InputCamera::updateDirectlyFromKeyboard()
		{
			InputControls* input = InputControls::getInstance();
			float t = task::gpu::Scheduler::getInstance()->getSecondsSinceLastFrame();
			const Uint8 *keys = SDL_GetKeyboardState(NULL);

			float speed = mMoveSpeed * t;
			SDL_Keycode k = input->getKeyCodeForCommand(InputCommandType::STRAFE_LEFT);
			Uint8 val = keys[k];
			mPosition.move(DRVector3(
				(keys[input->getKeyCodeForCommand(InputCommandType::STRAFE_LEFT)]-keys[input->getKeyCodeForCommand(InputCommandType::STRAFE_RIGHT)])*speed,
				(keys[input->getKeyCodeForCommand(InputCommandType::STRAFE_DOWN)]-keys[input->getKeyCodeForCommand(InputCommandType::STRAFE_UP)])*speed,
				(keys[input->getKeyCodeForCommand(InputCommandType::ACCELERATE)]-keys[input->getKeyCodeForCommand(InputCommandType::RETARD)])*speed));
			speed = mRotationSpeed * t;
			mRotation.rotateRel(DRVector3(
				(-keys[input->getKeyCodeForCommand(InputCommandType::ROTATE_UP)]+keys[input->getKeyCodeForCommand(InputCommandType::ROTATE_DOWN)])*speed,
				(-keys[input->getKeyCodeForCommand(InputCommandType::ROTATE_LEFT)]+keys[input->getKeyCodeForCommand(InputCommandType::ROTATE_RIGHT)])*speed,
				(-keys[input->getKeyCodeForCommand(InputCommandType::TILT_LEFT)]+keys[input->getKeyCodeForCommand(InputCommandType::TILT_RIGHT)])*speed));
		}
		DRReturn InputCamera::input(InputCommandType in)
		{
			float t = task::gpu::Scheduler::getInstance()->getSecondsSinceLastFrame();

			return DR_OK;
		}
	}
}