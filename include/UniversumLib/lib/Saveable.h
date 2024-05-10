#ifndef __UNIVERSUM_LIB_LIB_SAVEABLE_H
#define __UNIVERSUM_LIB_LIB_SAVEABLE_H

#include "UniversumLib/export.h"

#include "DRCore2/DRTypes.h"
#include "DRCore2/Threading/DRTask.h"

#include <string>
#include <memory>

namespace UniLib {
	namespace lib {
		/*
		* @author einhornimmond
		* @date 05.05.2024
		* @brief class for saveable object like textures or savegame state
		*/
		class UNIVERSUMLIB_EXPORT Saveable
		{
		public:
			Saveable(const char* fileName) : mFileName(fileName) {}
			Saveable() {}
			virtual ~Saveable();

			// gpu work
			virtual DRReturn downloadFromGPU() { return DR_NOT_IMPLEMENTED; }
			// storage work
			virtual DRReturn saveIntoFile() = 0;

			// start storage thread which will call saveIntoFile
			void asyncSave(std::shared_ptr<DRCommand> finishCommand, bool downloadFromGpu = false);

		protected:
			std::string mFileName;
			std::weak_ptr<DRTask> mStorageTask;
		};
	}
}





#endif //__UNIVERSUM_LIB_LIB_SAVEABLE_H