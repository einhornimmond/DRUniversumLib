#include "UniversumLib/model/BlockSector.h"
#include "UniversumLib/view/BlockSector.h"

namespace UniLib {
	namespace view {

		BlockSector::BlockSector(model::BlockSector* viewSector /* = NULL */)
			: Sector(dynamic_cast<model::Sector*>(viewSector))
		{

		}

		BlockSector::~BlockSector()
		{

		}


		DRReturn BlockSector::updateVisibility(view::Camera* camera)
		{
			return DR_OK;
		}

		DRReturn BlockSector::render(view::Camera* camera, float timeSinceLastFrame)
		{
			return DR_OK;
		}
	}
}