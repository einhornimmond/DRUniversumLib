#ifndef __UNIVERSUM_LIB_TYPE_UNIT_TYPE_H
#define __UNIVERSUM_LIB_TYPE_UNIT_TYPE_H

namespace UniLib {
	enum class UnitType
	{
		NONE = 0,
		LENGTH = 1, // meter - length
		AREA = 2, // qm - A
		VOLUME = 3, // m³ - Volume
		WEIGHT = 4, // g
		TEMPERATURE = 5, // temperature in °C
		TIME = 6, // time in seconds 
		VELOCITY = 7, //speed m/s
		ACCELERATION = 8 // m/s²
	};
}

#endif //__UNIVERSUM_LIB_TYPE_UNIT_TYPE_H