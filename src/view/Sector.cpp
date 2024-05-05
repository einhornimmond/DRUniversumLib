#include "Universumlib/view/Sector.h"

namespace UniLib {
	namespace view {
		
		// constructor
		Sector::Sector(model::Sector* sektorModel/* = NULL*/)
			: mSectorModel(sektorModel)
		{
		}
		// -------------------------------------------------------------
		// deconstructor
		Sector::~Sector() 
		{
		}

	};
};