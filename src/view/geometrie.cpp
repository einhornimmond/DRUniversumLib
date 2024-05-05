#include "UniversumLib/view/Geometrie.h"
#include "UniversumLib/model/geometrie/BaseGeometrie.h"

namespace UniLib {
	namespace view {

		

		Geometrie::Geometrie(model::geometrie::BaseGeometriePtr baseGeometrie)
			: lib::Loadable(LoadingStateType::HAS_INFORMATIONS), mGeometrieModel(baseGeometrie)
		{

		}

		Geometrie::Geometrie()
		{

		}

		Geometrie::~Geometrie()
		{
			//DR_SAVE_DELETE(mGeometrieModel);
		}
	}
}