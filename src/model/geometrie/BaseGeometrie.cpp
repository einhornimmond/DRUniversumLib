#include "model/geometrie/BaseGeometrie.h"
#include "model/geometrie/BaseGeometrieContainer.h"

namespace UniLib {
	namespace model {
		namespace geometrie {

			BaseGeometrie::BaseGeometrie(BaseGeometrieContainer* geometrieContainer)
				: mContainer(geometrieContainer) 
			{
				if(g_RenderBinder) mContainer = g_RenderBinder->newGeometrieContainer();
				else LOG_ERROR_VOID("render binder not set");
			
			}

			BaseGeometrie::~BaseGeometrie()
			{

			}
		}
	}
}