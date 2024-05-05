#ifndef __UNIVERSUM_LIB_TYPE_INPUT_COMMAND_TYPE_H
#define __UNIVERSUM_LIB_TYPE_INPUT_COMMAND_TYPE_H

#include "DRCore2/DRTypes.h"

namespace UniLib {
	/*
	* Input Action Types for custom mapping on keys
	*/
	enum class InputCommandType : u8
	{
		UNKNOWN = 0,
		ROTATE_LEFT = 1,
		ROTATE_RIGHT = 3,
		ROTATE_UP = 4,
		ROTATE_DOWN = 5,
		TILT_LEFT = 6,
		TILT_RIGHT = 7,
		STRAFE_LEFT = 8,
		STRAFE_RIGHT = 9,
		STRAFE_UP = 10,
		STRAFE_DOWN = 11,
		ACCELERATE = 12,
		// verzögern, pull down speed
		RETARD = 13,
		ATTACK_1 = 14,
		ATTACK_2 = 15,
		OPEN_MAIN_MENU = 16,
		JUMP = 17,
		PRIMARY_ACTION = 18,
		SECONDARY_ACTION = 19,
		LEFT_MOUSE_CLICK = 20,
		RIGHT_MOUSE_CLICK = 21,
		MIDDLE_MOUSE_CLICK = 22
	};
}

#endif //__UNIVERSUM_LIB_TYPE_INPUT_COMMAND_TYPE_H