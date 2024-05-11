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

#ifndef __DR_UNIVERSUM_LIB_CONTROLLER_SHADER_MANAGER__
#define __DR_UNIVERSUM_LIB_CONTROLLER_SHADER_MANAGER__

#include "UniversumLib/model/ShaderProgram.h"

#include "DRCore2/Threading/DRMultithreadContainer.h"

#include <map>
#include <vector>

namespace UniLib {	
	namespace manager {
		class UNIVERSUMLIB_EXPORT ShaderManager : public DRMultithreadContainer
		{
		public:
		
			static ShaderManager* const getInstance();
			inline static bool	isInitialized()	{return getInstance()->mInitalized;};

			DRReturn init(const char* shaderBasePath);

			void exit();

			//! lädt oder return instance auf Textur
			model::ShaderProgramPtr getShaderProgram(const char* shaderProgramName, const std::vector<model::ShaderInformation>& shaderInformations);
			inline model::ShaderProgramPtr getShaderProgram(const char* shaderProgramName) { return getShaderProgram(makeShaderHash(shaderProgramName)); }

			model::ShaderPtr getShader(const model::ShaderInformation& shaderInfos);

			inline const char* getShaderBasePath() const { return mShaderBasePath.data(); }
		protected:
			ShaderManager();
			ShaderManager(const ShaderManager&);
			virtual ~ShaderManager() {if(mInitalized) exit();};

			model::ShaderProgramPtr getShaderProgram(DHASH id);
			DHASH makeShaderHash(const char* shaderProgramName);

			std::string mShaderBasePath;

			//DRHashList mShaderEntrys;
			std::map<DHASH, model::ShaderProgramPtr>               mShaderProgramEntrys;
			std::map<DHASH, model::ShaderPtr>                      mShaderEntrys;
			bool                                            mInitalized;
#ifdef DEBUG
			std::map<DHASH, std::string>			mHashCollisionCheckMap;
#endif
		};

	}
}

#endif //__DR_UNIVERSUM_LIB_CONTROLLER_SHADER_MANAGER__