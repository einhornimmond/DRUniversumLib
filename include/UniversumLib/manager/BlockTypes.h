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

#ifndef __UNIVERSUM_LIB_CONTROLLER_BLOCK_MATERIAL_MANAGER_H
#define __UNIVERSUM_LIB_CONTROLLER_BLOCK_MATERIAL_MANAGER_H
/*!
 * \author Dario Rekowski
 * 
 * \date 07.01.16
 * 
 * \desc Manager for all Material Types in Game, import material template from json
 * 
 */

#include "UniversumLib/lib/Loadable.h"
#include "UniversumLib/model/block/BlockType.h"

#include "DRCore2/Threading/DRMultithreadContainer.h"
#include "DRCore2/Foundation/DRHash.h"

#include <map>

namespace UniLib {
	namespace manager {		
		
		class UNIVERSUMLIB_EXPORT BlockTypes : public lib::Loadable, protected DRMultithreadContainer
		{
		public:
			static BlockTypes* getInstance();
			//!
			//! \param materialConfigFiles move vector
			DRReturn init(std::vector<std::string> materialConfigFiles);
			// calling after every object using MaterialBlocks was cleaned up
			void exit();

			inline model::block::BlockType* getBlockType(HASH id);
			inline model::block::BlockType* getBlockType(const char* name) { return getBlockType(DRMakeStringHash(name));}

			// ------  implemented from loadable -------			
			//! actuall load code
			virtual DRReturn load(LoadingStateType target);
			// -----------------------------------------

		protected:
			// ------  implemented from loadable -------			
			virtual LoadingStateType detectLoadingState();
			// -----------------------------------------

			BlockTypes();
			virtual ~BlockTypes();

			DRReturn parsingJsonToBlockTypes(const std::string& fileContent);

			// for loading
			// if loading state has informations = filename
			// if loading state storage data ready = actuall file content
			std::vector<std::string> mMaterialConfigFileNames;
			std::vector<std::string> mMaterialConfigFileContents;

			// member variables
			DRMultithreadContainer mWorkMutex;
			typedef std::map<HASH, model::block::BlockType*> BlockTypeMap;
			BlockTypeMap mBlockTypes;

		private:	

		};
	}
}

#endif //__UNIVERSUM_LIB_CONTROLLER_BLOCK_MATERIAL_MANAGER_H