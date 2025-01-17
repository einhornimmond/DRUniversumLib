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

#include "UniversumLib.h" 

namespace UniLib {
	
	namespace model {
		namespace geometrie {

			enum GeometrieDataType {
				GEOMETRIE_NONE = 0,
				GEOMETRIE_VERTICES = 1,
				GEOMETRIE_COLORS = 2,
				GEOMETRIE_NORMALS = 4,
				GEOMETRIE_TEX2D_1 = 8,
				GEOMETRIE_TEX2D_2 = 16,
				GEOMETRIE_TEX2D_3 = 32,
				GEOMETRIE_TEX2D_4 = 64,
				GEOMETRIE_3DVECTOR = GEOMETRIE_VERTICES + GEOMETRIE_NORMALS,
				GEOMETRIE_2DVECTOR = GEOMETRIE_TEX2D_1 + GEOMETRIE_TEX2D_2 + GEOMETRIE_TEX2D_3 + GEOMETRIE_TEX2D_4,
				GEOMETRIE_4DVECTOR = GEOMETRIE_COLORS,
				GEOMETRIE_MAX = 128
			};

			enum GeometrieRenderMode {
				GEOMETRIE_RENDER_POINTS,
				GEOMETRIE_RENDER_LINES,
				GEOMETRIE_RENDER_LINE_STRIP,
				GEOMETRIE_RENDER_LINE_LOOP,
				GEOMETRIE_RENDER_TRIANGLES,
				GEOMETRIE_RENDER_TRIANGLE_STRIP,
				GEOMETRIE_RENDER_TRIANGLE_FAN,
				GEOMETRIE_RENDER_MAX
			};

			class UNIVERSUM_LIB_API BaseGeometrie : public DRIResource
			{
			public:
				BaseGeometrie();
				virtual ~BaseGeometrie();

				virtual void generateVertices(GeometrieDataType type) {};

				virtual const char* getResourceType() const {return "model::geometrie::BaseGeometrie";}
				// simple compare pointer adresses
				virtual bool less_than(DRIResource& b) const {return this < &b;}

				//! \brief type allowed: GEOMETRIE_VERTICES, GEOMETRIE_NORMALS
				__inline__ void addVector(DRVector3 v3, GeometrieDataType type);
				//! \brief type allowed: GEOMETRIE_TEX2D_1, GEOMETRIE_TEX2D_2, GEOMETRIE_TEX2D_3 or GEOMETRIE_TEX2D_4
				__inline__ void addVector(DRVector2 v2, GeometrieDataType type);
				//! \brief type allowed: GEOMETRIE_COLORS
				__inline__ void addVector(DRColor c, GeometrieDataType type);
				__inline__ void addIndice(int index);

				DRReturn copyToFastAccess();
				void deleteFillingStructures();
				void deleteFastAccessStructures();


				__inline__ GeometrieDataType getGeometrieDataFlags() {return mVertexFormatFlags;}

				// data access
				// vertex data
				__inline__ int getVertexSize() {return mVertexSize;}
				__inline__ int getVertexCount() {return mVertexCount;}
				__inline__ float* getVertices() {return mVertices;}
				__inline__ float getVertex(int i) {assert(i >= 0 && i < mVertexCount*mVertexSize); return mVertices[i];}
				// format
				__inline__ GeometrieDataType getFormatFlags() { return mVertexFormatFlags;}
				// indices
				__inline__ int getIndexCount() {return mIndiceCount;}
				__inline__ int getIndexCountFromVector() { return mIndices.size(); }
				__inline__ int* getIndices() {return mIndicesArray;}
				__inline__ int getIndex(int i) {assert(i >= 0 && i < mIndiceCount); return mIndices[i];}

				__inline__ void setRenderMode(GeometrieRenderMode renderMode) { mRenderMode = renderMode; }
				__inline__ GeometrieRenderMode getRenderMode() { return mRenderMode; }

			protected:

				class UNIVERSUM_LIB_API GeometriePartVector 
				{
				public:
					GeometriePartVector(GeometrieDataType type):mType(type) {}
					~GeometriePartVector(){}

					__inline__ void addVector(DRVector3 v3);
					__inline__ void addVector(DRVector2 v2);
					__inline__ void addVector(DRColor c);
					__inline__ DRVector3 getVector3 (int index); 
					__inline__ DRVector2 getVector2 (int index);
					__inline__ DRColor   getColor(int index);

					__inline__ GeometrieDataType getType() {return mType;}
					int		   getTypeSize();
					int		   getVertexCount();

				protected:
					GeometrieDataType mType;
					std::vector<float> mRawData;

					__inline__ void addFloats(float* c, int count);
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

			typedef DRResourcePtr<BaseGeometrie> BaseGeometriePtr;

		}
	}
}


#endif //__UNIVERSUM_LIB_MODEL_GEOMETRIE_BASE_GEOMETRIE__H