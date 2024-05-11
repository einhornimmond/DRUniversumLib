#ifndef __UNIVERSUM_LIB_MODEL_SHADER_H
#define __UNIVERSUM_LIB_MODEL_SHADER_H

#include "UniversumLib/export.h"
#include "UniversumLib/type/ShaderType.h"
#include "UniversumLib/lib/Loadable.h"

#include "DRCore2/Foundation/DRIResource.h"
#include "DRCore2/DRTypes.h"

namespace UniLib {
	namespace model {

		struct UNIVERSUMLIB_EXPORT ShaderInformation
		{
			ShaderInformation(const char* shaderFileName, ShaderType shaderType)
				: fileName(shaderFileName), type(shaderType) {}
			std::string fileName;
			ShaderType type;
			
		};

		// Shader Model for a single Shader
		class UNIVERSUMLIB_EXPORT Shader : public DRIResource, public lib::Loadable, protected DRMultithreadContainer
		{
		public:
			Shader(const char* shaderFileName, ShaderType shaderType);
			Shader(const model::ShaderInformation& infos);
			virtual ~Shader();


			inline HASH getID() { return mID; }

			virtual const char* getResourceType() const { return "Shader"; }
			virtual bool less_than(DRIResource& shader) const
			{
				return mID < dynamic_cast<Shader&>(shader).mID;
			}

			
			virtual DRReturn compileOnGPU() = 0;
			virtual bool parsedOnGPU() = 0;

			// ------  implemented from loadable -------
			//! actuall load code
			virtual DRReturn load(LoadingStateType target);
			// -----------------------------------------

		protected:
			void loadFromFile();
			// ------  implemented from loadable -------
			//! detect current loading state
			virtual LoadingStateType detectLoadingState();
			// -----------------------------------------

			ShaderType mType;
			std::string mFileName;
			std::string mShaderSource;

		private:
			HASH mID;

		};

		typedef std::shared_ptr<Shader> ShaderPtr;
	}
}

#endif //__UNIVERSUM_LIB_MODEL_SHADER_H
