#ifndef __UNIVERSUM_LIB_MODEL_SHADER_PROGRAM_BINARY_H
#define __UNIVERSUM_LIB_MODEL_SHADER_PROGRAM_BINARY_H

#include "UniversumLib/UniversumLib.h"
#include "UniversumLib/lib/Loadable.h"
#include "UniversumLib/lib/Saveable.h"


/*
* TODO: check if supported on current hardware
glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &formats);
if( formats < 1 ) {
  std::cerr << "Driver does not support any binary formats." << std::endl;
  exit(EXIT_FAILURE);
}
*/

namespace UniLib {
	namespace model {
		class UNIVERSUMLIB_EXPORT ShaderProgamBinary: public lib::Loadable, public lib::Saveable, protected DRMultithreadContainer
		{
		public:
			ShaderProgamBinary(const char* fileName);
			virtual ~ShaderProgamBinary();

			// ------  implemented from loadable -------
			//! actuall load code
			virtual DRReturn load(LoadingStateType target);
			// -----------------------------------------

			DRReturn saveIntoFile();
			// check if opengl support binary files and if file exist
			virtual bool isFileExist() = 0;
		protected:
			// ------  implemented from loadable -------
			//! detect current loading state
			virtual LoadingStateType detectLoadingState();
			// -----------------------------------------

			DRReturn loadFromFile();			

			std::string mBinaryData;
			GLenum mBinaryFormat;
			std::string mFileName;
		};

		typedef std::shared_ptr<ShaderProgamBinary> ShaderProgamBinaryPtr;
	}
}

#endif //__UNIVERSUM_LIB_MODEL_SHADER_PROGRAM_BINARY_H