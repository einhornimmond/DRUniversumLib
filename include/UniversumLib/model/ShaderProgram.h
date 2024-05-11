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

#include "UniversumLib/export.h"

#include "Shader.h"
#include "ShaderProgramBinary.h"

#include "DRCore2/Foundation/DRIResource.h"

namespace UniLib {
	namespace controller {
		class CPUSheduler;
		class ShaderManager;
	}
	namespace model {
		

		// Class for a ShaderProgram, containing vertex shader + pixel shader + ...
		class UNIVERSUMLIB_EXPORT ShaderProgram : public DRIResource, public lib::Loadable, protected DRMultithreadContainer
		{
		public:
			ShaderProgram(const char* name, std::vector<ShaderPtr> shaders, HASH id = 0);
			ShaderProgram(const char* name, ShaderProgamBinaryPtr shaderProgramBinary, HASH id = 0);
			virtual ~ShaderProgram();

			virtual void bind() const = 0;
			virtual void unbind() = 0;


			//inline GLuint getProgram() {return mProgram;}
			inline HASH getID() { return mId; }
			inline const char* getName() { return mName.data(); }

			virtual const char* getResourceType() const { return "ShaderProgram"; }
			virtual bool less_than(DRIResource& shader) const
			{
				return mId < dynamic_cast<ShaderProgram&>(shader).mId;
			}

			// ------  implemented from loadable -------			
			//! actuall load code, called from loading thread
			virtual DRReturn load(LoadingStateType target);
			virtual bool isReadyForLoad(LoadingStateType target);
			// -----------------------------------------			

		protected:
			virtual DRReturn attachShaderToProgam() = 0;
			

			// ------  implemented from loadable -------
			//! detect current loading state
			virtual LoadingStateType detectLoadingState() = 0;
			// -----------------------------------------

			HASH  mId;			
			std::string mName;
			std::vector<ShaderPtr> mShaders;
			ShaderProgamBinaryPtr mShaderProgramBinary;
		};

		typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;
	}
}



#endif	/* __UNIVERSUM_LIB_MODEL_SHADER_PROGRAM_H */