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

/*!
 * 
 * \author: Dario Rekowski
 * 
 * \date: 31.10.2015
 * 
 * \desc Base class for geometrie models
 *
 */

#ifndef __UNIVERSUM_LIB_MODEL_GEOMETRIE_BASE_GEOMETRIE__H
#define __UNIVERSUM_LIB_MODEL_GEOMETRIE_BASE_GEOMETRIE__H

#include "UniversumLib/export.h" 
#include "UniversumLib/type/GeometrieDataType.h"
#include "UniversumLib/type/GeometrieRenderMode.h"

#include "DRCore2/DRTypes.h"
#include "DRCore2/Foundation/DRVector2.h"
#include "DRCore2/Foundation/DRVector3.h"
#include "DRCore2/Foundation/DRColor.h"
#include "DRCore2/Foundation/DRIResource.h"

#include <cassert>
#include <vector>
#include <map>

namespace UniLib {
	
	namespace model {
		namespace geometrie {
			class UNIVERSUMLIB_EXPORT BaseGeometrie : public DRIResource
			{
			public:
				BaseGeometrie();
				virtual ~BaseGeometrie();

				virtual void generateVertices(GeometrieDataType type) {};

				virtual const char* getResourceType() const {return "model::geometrie::BaseGeometrie";}
				// simple compare pointer adresses
				virtual bool less_than(DRIResource& b) const {return this < &b;}

				//! \brief type allowed: GEOMETRIE_VERTICES, GEOMETRIE_NORMALS
				inline void addVector(DRVector3 v3, GeometrieDataType type);
				//! \brief type allowed: GEOMETRIE_TEX2D_1, GEOMETRIE_TEX2D_2, GEOMETRIE_TEX2D_3 or GEOMETRIE_TEX2D_4
				inline void addVector(DRVector2 v2, GeometrieDataType type);
				//! \brief type allowed: GEOMETRIE_COLORS
				inline void addVector(DRColor c, GeometrieDataType type);
				inline void addIndice(int index);

				DRReturn copyToFastAccess();
				void deleteFillingStructures();
				void deleteFastAccessStructures();


				inline GeometrieDataType getGeometrieDataFlags() {return mVertexFormatFlags;}

				// data access
				// vertex data
				inline int getVertexSize() {return mVertexSize;}
				inline int getVertexCount() {return mVertexCount;}
				inline float* getVertices() {return mVertices;}
				inline float getVertex(int i) {assert(i >= 0 && i < mVertexCount*mVertexSize); return mVertices[i];}
				// format
				inline GeometrieDataType getFormatFlags() { return mVertexFormatFlags;}
				// indices
				inline int getIndexCount() {return mIndiceCount;}
				inline int getIndexCountFromVector() { return mIndices.size(); }
				inline int* getIndices() {return mIndicesArray;}
				inline int getIndex(int i) {assert(i >= 0 && i < mIndiceCount); return mIndices[i];}

				inline void setRenderMode(GeometrieRenderMode renderMode) { mRenderMode = renderMode; }
				inline GeometrieRenderMode getRenderMode() { return mRenderMode; }

			protected:

				class UNIVERSUMLIB_EXPORT GeometriePartVector
				{
				public:
					GeometriePartVector(GeometrieDataType type):mType(type) {}
					~GeometriePartVector(){}

					inline void addVector(DRVector3 v3);
					inline void addVector(DRVector2 v2);
					inline void addVector(DRColor c);
					inline DRVector3 getVector3 (int index); 
					inline DRVector2 getVector2 (int index);
					inline DRColor   getColor(int index);

					inline GeometrieDataType getType() {return mType;}
					int		   getTypeSize();
					int		   getVertexCount();

				protected:
					GeometrieDataType mType;
					std::vector<float> mRawData;

					inline void addFloats(float* c, int count);
				};

				// filling structure
				typedef std::map<GeometrieDataType, GeometriePartVector*>::iterator GeometrieDataMapIterator;
				typedef std::pair<GeometrieDataType, GeometriePartVector*> GeometrieDataMapPair;
				std::map<GeometrieDataType, GeometriePartVector*> mGeometrieDataMap;
				std::vector<int> mIndices;

				// fast access structure
				int*		mIndicesArray;
				int			mIndiceCount;
				float*		mVertices;
				int			mVertexCount;
				GeometrieDataType mVertexFormatFlags;
				int			mVertexSize;
				GeometrieRenderMode mRenderMode;

				GeometriePartVector* getGeometriePartVector(GeometrieDataType type);
			};
		}
	}
}


#endif //__UNIVERSUM_LIB_MODEL_GEOMETRIE_BASE_GEOMETRIE__H