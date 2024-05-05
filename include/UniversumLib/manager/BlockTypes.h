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

#include "UniversumLib/export.h"
#include "DRCore2/Threading/DRCPUTask.h"
#include "DRCore2/Threading/DRCPUScheduler.h"
#include "DRCore2/Threading/DRMultithreadContainer.h"
#include "DRCore2/Foundation/DRHash.h"

#include <map>

namespace UniLib {
	namespace model {
		namespace block {
			class BlockType;	
		}
	}
	namespace controller {

		// task for parsing block type data
		class BlockTypeLoadingTask: public DRCPUTask
		{
		public:
			BlockTypeLoadingTask(DRCPUScheduler* scheduler, std::string fileContent)
				: DRCPUTask(scheduler), mFileContent(fileContent) {}

			virtual DRReturn run();
			virtual bool isTaskFinished() {return false;};
			virtual const char* getResourceType() const { return "BlockTypeLoadingTask"; };
		protected:
			std::string mFileContent;


		};
		// task for loading files from harddisk
		class LoadingJsonFilesIntoMemoryTask : public DRCPUTask
		{
		public:
			LoadingJsonFilesIntoMemoryTask(std::string filename, DRCPUScheduler* schedulerForParser)
				: DRCPUTask(g_HarddiskScheduler), mFileName(filename), mSchedulerForParser(schedulerForParser) {
#ifdef _UNI_LIB_DEBUG
				setName(filename.data());
#endif //_UNI_LIB_DEBUG
			}

			virtual DRReturn run();
			virtual bool isTaskFinished() { return false; };
			virtual const char* getResourceType() const { return "LoadingJsonFilesIntoMemoryTask"; };
		protected:
			std::string mFileName;
			DRCPUScheduler* mSchedulerForParser;
		};

		class UNIVERSUMLIB_EXPORT BlockTypeManager : protected DRMultithreadContainer
		{
			friend BlockTypeLoadingTask;
			friend LoadingJsonFilesIntoMemoryTask;
		public:
			static BlockTypeManager* getInstance();
			DRReturn init(const std::list<std::string>* filenames);
			DRReturn initAsyn(const std::list<std::string>* filenames, DRCPUScheduler* scheduler);
			// calling after every object using MaterialBlocks was cleaned up
			void exit();

			inline LoadingState checkLoadingState() { UNIQUE_LOCK; return mLoadingState; }
			inline model::block::BlockType* getBlockType(HASH id);
			inline model::block::BlockType* getBlockType(const char* name) { return getBlockType(DRMakeStringHash(name));}


		protected:
			BlockTypeManager();
			virtual ~BlockTypeManager();

			DRReturn _parsingJsonToBlockTypes(const std::string& mFilesContent);

			// member variables
			DRMultithreadContainer mWorkMutex;
			typedef std::map<HASH, model::block::BlockType*> BlockTypeMap;
			typedef std::pair<HASH, model::block::BlockType*> BlockTypePair;
			typedef BlockTypeMap::iterator BlockTypelIter;
			BlockTypeMap mBlockTypes;

		private:
			LoadingState mLoadingState;
			

		};
	}
}

#endif //__UNIVERSUM_LIB_CONTROLLER_BLOCK_MATERIAL_MANAGER_H