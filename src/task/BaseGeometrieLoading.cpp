#include "UniversumLib/task/BaseGeometrieLoading.h"
#include "UniversumLib/type/BaseGeometrieType.h"
#include "UniversumLib/type/GeometrieDataType.h"
#include "UniversumLib/manager/BaseGeometries.h"

#include "UniversumLib/model/geometrie/Plane.h"

#include "DRCore2/DRCore2Main.h"

namespace UniLib {
	namespace task {
		DRReturn BaseGeometrieLoading::run()
		{
			model::geometrie::BaseGeometriePtr geo;
			switch (mGeometrieType) {
			case BaseGeometrieType::PLANE :
				geo.reset(new model::geometrie::Plane(GeometrieDataType::VERTICES));
				break;
			}
			if (!geo) {
				DRLog.writeToLog("type: %d", mGeometrieType);
				LOG_ERROR("hasn't found geo base type implementation", DR_ERROR);
			}
			mGeometrieView->setBaseGeometrie(geo);
			mGeometrieView->asyncLoad(LoadingStateType::GPU_DATA_READY);			
			return DR_OK;
		}
	}
}


