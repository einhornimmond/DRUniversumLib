#ifndef __UNIVERSUM_LIB_TASK_CPU_BASE_GEOMETRIE_LOADING_H
#define __UNIVERSUM_LIB_TASK_CPU_BASE_GEOMETRIE_LOADING_H

#include "DRCore2/Threading/DRCPUTask.h"
#include "UniversumLib/type/BaseGeometrieType.h"
#include "UniversumLib/view/Geometrie.h"

namespace UniLib {
	namespace task {

		class BaseGeometrieLoading : public DRCPUTask {
		public:
			BaseGeometrieLoading(DRCPUScheduler* scheduler, BaseGeometrieType geoType, view::GeometriePtr emptyGeometrieView)
				: DRCPUTask(scheduler), mGeometrieType(geoType), mGeometrieView(emptyGeometrieView) {}
			virtual DRReturn run();
			virtual const char* getResourceType() const { return "task::cpu::BaseGeometrieLoading"; };
		protected:
			BaseGeometrieType mGeometrieType;
			view::GeometriePtr mGeometrieView;			
		};
	}
}



#endif //__UNIVERSUM_LIB_TASK_CPU_BASE_GEOMETRIE_LOADING_H