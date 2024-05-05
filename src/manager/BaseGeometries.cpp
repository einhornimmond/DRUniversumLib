#include "UniversumLib/manager/BaseGeometries.h"
#include "UniversumLib/model/geometrie/BaseGeometrie.h"
#include "UniversumLib/model/geometrie/Plane.h"
#include "UniversumLib/view/Geometrie.h"
#include "UniversumLib/controller/BindToRenderer.h"
#include "UniversumLib/task/BaseGeometrieLoading.h"

#include "DRCore2/DRCore2Main.h"

#include "magic_enum/magic_enum_utility.hpp"

namespace UniLib {
	namespace manager {

		BaseGeometries* BaseGeometries::getInstance()
		{
			static BaseGeometries theOne;
			return &theOne;
		}

		BaseGeometries::BaseGeometries()
			: mCPUScheduler(NULL), mInitalized(false)
		{
		}
		BaseGeometries::~BaseGeometries()
		{
			exit();
		}
		
		void BaseGeometries::exit()
		{
			// release all geometrie pointer
			magic_enum::enum_for_each<BaseGeometrieType>([&](auto val) {
				constexpr BaseGeometrieType baseGeometrieType = val;
				if (baseGeometrieType == BaseGeometrieType::ENTRY_COUNT) return;
				mGeometrieArray[magic_enum::enum_integer(baseGeometrieType)].reset();
			});
			mInitalized = false;
		}

		DRReturn BaseGeometries::init(DRCPUScheduler* cpuScheduler/* = NULL*/)
		{
			mCPUScheduler = cpuScheduler;
			mInitalized = true;
			return DR_OK;
		}

		view::GeometriePtr BaseGeometries::getGeometrie(BaseGeometrieType type)
		{
			assert(type < BaseGeometrieType::ENTRY_COUNT);
			assert(mInitalized == true);
			
			auto geometriePtr = mGeometrieArray[magic_enum::enum_integer(type)];
			if (!geometriePtr) {
				{
					std::unique_lock _lock(mMutex);
					geometriePtr.reset(g_RenderBinder->newGeometrie(nullptr));
				}
				DRTaskPtr task(new task::BaseGeometrieLoading(mCPUScheduler, type, geometriePtr));
#ifdef DEBUG
				if (type == BaseGeometrieType::PLANE)
					task->setName("Plane");
#endif
				task->scheduleTask(task);
			}

			return geometriePtr;
		}

	}
}