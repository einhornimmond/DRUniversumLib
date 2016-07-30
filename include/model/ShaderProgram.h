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

/* 
 * File:   Shader.h
 * Author: Dario
 *
 * Created on 30. Oktober 2011, 19:45
 */

#ifndef __UNIVERSUM_LIB_MODEL_SHADER_PROGRAM_H
#define	__UNIVERSUM_LIB_MODEL_SHADER_PROGRAM_H

#include "UniformSet.h"
#include "lib/MultithreadResource.h"
#include "controller/CPUTask.h"
#include "controller/GPUTask.h"

namespace UniLib {
	namespace controller {
		class CPUSheduler;
		class ShaderManager;
	}
	namespace model {

		

		struct UNIVERSUM_LIB_API ShaderProgramParameter
		{
			ShaderProgramParameter() {};
			ShaderProgramParameter(const char* _vertexShaderName, const char* _fragmentShaderName)
				: vertexShaderName(_vertexShaderName), fragmentShaderName(_fragmentShaderName)
			{

			}

			DRString vertexShaderName;
			DRString fragmentShaderName;

		};

		enum UNIVERSUM_LIB_API ShaderType {
			SHADER_NONE = 0,
			SHADER_FRAGMENT = 1,
			SHADER_VERTEX = 2,
			SHADER_TESSELATION = 3,
			SHADER_TESSELATION_EVALUATION = 4,
			SHADER_GEOMETRIE = 5
		};

		

		class UNIVERSUM_LIB_API Shader : public DRIResource
		{
		public:
			Shader(HASH id = 0);
			~Shader();

			virtual DRReturn init(const char* shaderFile, ShaderType shaderType) = 0;
			virtual DRReturn init(unsigned char* shaderFileInMemory, ShaderType type) = 0;
			
			__inline__ HASH getID() {return mID;}

			virtual const char* getResourceType() const {return "Shader";}
			virtual bool less_than(DRIResource& shader) const
			{
				return mID <  dynamic_cast<Shader&>(shader).mID;
			}


			static unsigned char* readShaderFile(const char *filename);
			
		protected:
			ShaderType mType;

		private:
			HASH mID;
			
		};

		typedef DRResourcePtr<Shader> ShaderPtr;
		class ShaderLoadingTask : public controller::CPUTask
		{
		public:
			ShaderLoadingTask(ShaderProgram* shader, controller::CPUSheduler* scheduler)
				: CPUTask(scheduler), mShaderProgram(shader) {}

			//! \brief called from task scheduler, maybe from another thread
			virtual DRReturn run(); 
			virtual const char* getResourceType() const { return "ShaderLoadingTask"; };

		protected:
			ShaderProgram* mShaderProgram;

		};
		class ShaderCompileTask;

		class UNIVERSUM_LIB_API ShaderProgram : public lib::MultithreadResource
		{
			friend ShaderLoadingTask;
			friend controller::ShaderManager;
			friend ShaderCompileTask;
		public:
			ShaderProgram(HASH id = 0);
			~ShaderProgram();

			//virtual DRReturn init(ShaderPtr vertexShader, ShaderPtr fragmentShader) = 0;
			DRReturn addShader(const char* filename, ShaderType type);

			virtual void bind() const = 0;
			virtual void unbind() = 0;


			//__inline__ GLuint getProgram() {return mProgram;}
			__inline__ HASH getID() {return mId;}
#ifdef _UNI_LIB_DEBUG
			__inline__ const char* getName() { return mName.data(); }
#endif

			virtual const char* getResourceType() const {return "ShaderProgram";}
			virtual bool less_than(DRIResource& shader) const
			{
				return mId < dynamic_cast<ShaderProgram&>(shader).mId;
			}

		protected:
			void loadShaderDataIntoMemory();
			virtual void parseShaderData() = 0;
			

			struct ShaderData {
				ShaderData(const char* filename, ShaderType type) 
					: filename(filename), shaderFileInMemory(NULL), type(type) {}
				std::string filename;
				unsigned char* shaderFileInMemory;
				ShaderType type;
			};
			HASH  mId;
			std::list<ShaderData> mShaderToLoad;
			std::list<Shader*> mLoadedShader;
			controller::TaskPtr mShaderCompileTask;
#ifdef _UNI_LIB_DEBUG
			std::string mName;
#endif
			//GLuint mProgram;
		};

		typedef DRResourcePtr<ShaderProgram> ShaderProgramPtr;

		class ShaderCompileTask : public controller::GPUTask
		{
		public:
			ShaderCompileTask(ShaderProgram* shader)
				: GPUTask(true), mShaderProgram(shader) {}
			virtual DRReturn run();
			virtual const char* getResourceType() const { return "ShaderCompileTask"; };
		protected:
			ShaderProgram* mShaderProgram;
			ShaderProgram::ShaderData* mShaderData;
		};
	}
}



#endif	/* __UNIVERSUM_LIB_MODEL_SHADER_PROGRAM_H */

