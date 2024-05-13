#include "UniversumLib/model/geometrie/Plane.h"
#include "UniversumLib/type/GeometrieRenderMode.h"

#include "magic_enum/magic_enum_flags.hpp"
using namespace magic_enum::bitwise_operators;

namespace UniLib {
	namespace model {
		namespace geometrie {

			Plane::Plane(GeometrieDataType type)
			{
				generateVertices(type);
			}
			
			Plane::~Plane()
			{

			}

			void Plane::generateVertices(GeometrieDataType type)
			{
				DRVector2 baseEdges[] = {DRVector2(0.0f), DRVector2(0.0f, 1.0f), DRVector2(1.0f, 0.0f), DRVector2(1.0f, 1.0f)};
				for(int i = 0; i < 4; i++) {
					if(magic_enum::enum_integer(type & GeometrieDataType::VERTICES)) {
						addVector(DRVector3(baseEdges[i].x, 0.0f, baseEdges[i].y), GeometrieDataType::VERTICES);
					}
					if(magic_enum::enum_integer(type & GeometrieDataType::NORMALS)) {
						addVector(DRVector3(0.0f, 1.0f, 0.0f), GeometrieDataType::NORMALS);
					}
					if(magic_enum::enum_integer(type & GeometrieDataType::TEX2D_1)) {
						addVector(baseEdges[i], GeometrieDataType::TEX2D_1);
					}
					addIndice(i);
				}
				setRenderMode(GeometrieRenderMode::TRIANGLE_STRIP);
				copyToFastAccess();
			}
		}
	}
}