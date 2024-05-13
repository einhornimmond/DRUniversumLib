#include "UniversumLib/view/block/GeometrieBlock.h"
#include "UniversumLib/model/block/GeometrieBlock.h"

namespace UniLib {
	namespace view {
		namespace block {

			GeometrieBlock::GeometrieBlock()
				: mMaterial(NULL), mGeometrie(NULL), mMatrixUniforms(NULL)
			{

			}

			GeometrieBlock::~GeometrieBlock()
			{

			}

			void GeometrieBlock::clearGeometrieBlockList()
			{
				for(auto it = mGeometrieBlockModels.begin(); it != mGeometrieBlockModels.end(); it++) {
					if(it->use_count() == 1) {
						it = mGeometrieBlockModels.erase(it);
					}
				}
			}
		}
	}
}