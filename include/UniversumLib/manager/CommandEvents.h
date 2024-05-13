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
#ifndef __UNIVERSUM_LIB_MANAGER_COMMAND_EVENT_MANAGER_H__
#define __UNIVERSUM_LIB_MANAGER_COMMAND_EVENT_MANAGER_H__

#include "UniversumLib/export.h"

#include "DRCore2/Threading/DRTask.h"
#include "DRCore2/Threading/DRMultithreadContainer.h"

#include <list>
#include <map>

namespace UniLib {
	namespace manager {
		class UNIVERSUMLIB_EXPORT CommandEvents: protected DRMultithreadContainer
		{
		public:
			CommandEvents();
			~CommandEvents();

			DRReturn init();
			void exit();

			DRReturn addCommandForEvent(const char* eventName, std::shared_ptr<DRCommand> command);
			DRReturn addCommandForEvent(HASH eventHash, std::shared_ptr<DRCommand> command);
			void removeCommandForEvent(const char* eventName, std::shared_ptr<DRCommand> command);
			void removeCommandForEvent(HASH eventHash, std::shared_ptr<DRCommand> command);

			void triggerEvent(const char* name, DRTask* task);
			void triggerEvent(HASH eventHash, DRTask* task);

		protected:
			typedef std::list<std::shared_ptr<DRCommand>> CommandList;
			std::map<HASH, CommandList> mCommandsMap;
#ifdef DEBUG
			// dubletten check
			typedef std::map<HASH, std::string> HashNameMap;
			HashNameMap mHashNameMap;			
#endif
		};

		class UNIVERSUMLIB_EXPORT CallEventManagerCommand : public DRCommand
		{
		public:
			CallEventManagerCommand(const char* eventName, DRTask* task, CommandEvents* eventManager)
				: mEventName(eventName), mFinishedTask(task), mEventManagerToCall(eventManager) {assert(eventManager != NULL);}
			virtual void taskFinished(DRTask* task) {mEventManagerToCall->triggerEvent(mEventName.data(), mFinishedTask);}
		protected:
			std::string mEventName;
			DRTask* mFinishedTask;
			CommandEvents* mEventManagerToCall;
		};
	}
}


#endif __UNIVERSUM_LIB_MANAGER_COMMAND_EVENT_MANAGER_H__