#ifndef __UNIVERSUM_LIB_TYPE_SHADER_TYPE_H
#define __UNIVERSUM_LIB_TYPE_SHADER_TYPE_H

namespace UniLib {

	// shader types
	enum class ShaderType {
		NONE = 0,
		FRAGMENT = 1,
		VERTEX = 2,
		TESSELATION = 3,
		TESSELATION_EVALUATION = 4,
		GEOMETRIE = 5
	};
}

#endif //__UNIVERSUM_LIB_TYPE_SHADER_TYPE_H