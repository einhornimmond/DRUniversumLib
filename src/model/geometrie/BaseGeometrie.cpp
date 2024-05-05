#include "UniversumLib/model/geometrie/BaseGeometrie.h"

#include "DRCore2/DRCore2Main.h"

#include "magic_enum/magic_enum.hpp"

namespace UniLib {
	namespace model {
		namespace geometrie {

			BaseGeometrie::BaseGeometrie()
			: mIndicesArray(nullptr), mIndiceCount(0), mVertices(nullptr), mVertexCount(0),
			  mVertexFormatFlags(GeometrieDataType::NONE), mVertexSize(0), mRenderMode(GeometrieRenderMode::TRIANGLES)
			{
			}
			
			BaseGeometrie::~BaseGeometrie()
			{
				deleteFillingStructures();
				deleteFastAccessStructures();
			}


			BaseGeometrie::GeometriePartVector* BaseGeometrie::getGeometriePartVector(GeometrieDataType type)
			{
				GeometrieDataMapIterator it = mGeometrieDataMap.find(type);
				if(it == mGeometrieDataMap.end()) {
					mGeometrieDataMap.insert(GeometrieDataMapPair(type, new GeometriePartVector(type)));
					it = mGeometrieDataMap.find(type);
					assert(it != mGeometrieDataMap.end());
			}
				return it->second;
			}
			void BaseGeometrie::addVector(DRVector3 v3, GeometrieDataType type)
			{
				getGeometriePartVector(type)->addVector(v3);
			}
			void BaseGeometrie::addVector(DRVector2 v2, GeometrieDataType type)
			{
				getGeometriePartVector(type)->addVector(v2);
			}
			void BaseGeometrie::addVector(DRColor c, GeometrieDataType type)
			{
				getGeometriePartVector(type)->addVector(c);
			}
			void BaseGeometrie::addIndice(int index)
			{
				mIndices.push_back(index);
			}

			DRReturn BaseGeometrie::copyToFastAccess()
			{
				deleteFastAccessStructures();
				int vertexCount = 0;
				for(GeometrieDataMapIterator it = mGeometrieDataMap.begin(); it != mGeometrieDataMap.end(); it++) {
					// combine flags, casting with magic_enum
					mVertexFormatFlags = magic_enum::enum_cast<GeometrieDataType>(
						magic_enum::enum_integer(mVertexFormatFlags) 
						| magic_enum::enum_integer(it->second->getType())
					).value();
					mVertexSize += it->second->getTypeSize();
					if(!vertexCount)
						vertexCount = it->second->getVertexCount();
					if(vertexCount != it->second->getVertexCount())
						LOG_ERROR("vertex Count isn't the same by all different vector datas", DR_ERROR);
				}
				mVertexCount = vertexCount;
				mVertices = new float[vertexCount*mVertexSize];
				for(int i = 0; i < vertexCount; i++) {
					int offset = 0;
					for(int y = 0; pow(2, y) < magic_enum::enum_integer(GeometrieDataType::ENTRY_COUNT); y++) {
						int x = pow(2, y);
						if(x & magic_enum::enum_integer(mVertexFormatFlags)) {
							GeometrieDataMapIterator it = mGeometrieDataMap.find(magic_enum::enum_cast<GeometrieDataType>(x).value());
							assert(it != mGeometrieDataMap.end());
							if(x & magic_enum::enum_integer(GeometrieDataType::VECTOR2D)) {
								memcpy(&mVertices[i*mVertexSize+offset], it->second->getVector2(i).c, sizeof(float)*2);
								offset+= 2;
							}
							else if(x & magic_enum::enum_integer(GeometrieDataType::VECTOR3D)) {
								memcpy(&mVertices[i*mVertexSize+offset], it->second->getVector3(i).c, sizeof(float)*3);
								offset += 3;
							}
							else if(x & magic_enum::enum_integer(GeometrieDataType::VECTOR4D)) {
								memcpy(&mVertices[i*mVertexSize+offset], it->second->getColor(i).c, sizeof(float)*4);
								offset += 4;
							}
						}
					}

			}

				//indices
				mIndiceCount = mIndices.size();
				mIndicesArray = new int[mIndiceCount];
				for(int i = 0; i < mIndiceCount; i++) {
					mIndicesArray[i] = mIndices[i];
		}
				return DR_OK;

	}
			void BaseGeometrie::deleteFillingStructures()
			{
				for(GeometrieDataMapIterator it = mGeometrieDataMap.begin(); it != mGeometrieDataMap.end(); it++) {
					DR_SAVE_DELETE(it->second);
				}
				mGeometrieDataMap.clear();
			}
			void BaseGeometrie::deleteFastAccessStructures()
			{
				mVertexFormatFlags = GeometrieDataType::NONE;
				mIndiceCount = 0;
				DR_SAVE_DELETE_ARRAY(mIndicesArray);
				mVertexSize = 0;
				mVertexCount = 0;
				DR_SAVE_DELETE_ARRAY(mVertices);
			}

			// ******************************************************************************************

			DRVector3 BaseGeometrie::GeometriePartVector::getVector3 (int index)
			{
				assert(
					magic_enum::enum_integer(mType) & magic_enum::enum_integer(GeometrieDataType::VECTOR3D)
					&& index < mRawData.size()*3
				);
				return DRVector3(&mRawData[index*3]);
			}

			DRVector2 BaseGeometrie::GeometriePartVector::getVector2(int index)
			{
				assert(
					magic_enum::enum_integer(mType) & magic_enum::enum_integer(GeometrieDataType::VECTOR2D)
					&& index < mRawData.size()*2
				);
				return DRVector2(&mRawData[index*2]);
			}

			DRColor BaseGeometrie::GeometriePartVector::getColor(int index)
			{
				assert(
					magic_enum::enum_integer(mType) & magic_enum::enum_integer(GeometrieDataType::VECTOR4D) 
					&& index < mRawData.size()*4);
				return DRColor(&mRawData[index*4]);
			}

			void BaseGeometrie::GeometriePartVector::addVector(DRVector2 v2)
			{
				assert(magic_enum::enum_integer(mType) & magic_enum::enum_integer(GeometrieDataType::VECTOR2D));
				addFloats(v2.c, 2);
			}
			void BaseGeometrie::GeometriePartVector::addVector(DRVector3 v3)
			{
				assert(magic_enum::enum_integer(mType) & magic_enum::enum_integer(GeometrieDataType::VECTOR3D));
				addFloats(v3.c, 3);
			}
			void BaseGeometrie::GeometriePartVector::addVector(DRColor c)
			{
				assert(magic_enum::enum_integer(mType) & magic_enum::enum_integer(GeometrieDataType::VECTOR4D));
				addFloats(c, 4);
			}
			void BaseGeometrie::GeometriePartVector::addFloats(float* c, int count)
			{
				for(int i = 0; i < count; i++)
					mRawData.push_back(c[i]);
			}	

			int BaseGeometrie::GeometriePartVector::getTypeSize()
			{
				if(magic_enum::enum_integer(mType) & magic_enum::enum_integer(GeometrieDataType::VECTOR2D)) return 2;
				if(magic_enum::enum_integer(mType) & magic_enum::enum_integer(GeometrieDataType::VECTOR3D)) return 3;
				if(magic_enum::enum_integer(mType) & magic_enum::enum_integer(GeometrieDataType::VECTOR4D)) return 4;
				return 0;
			}

			int BaseGeometrie::GeometriePartVector::getVertexCount()
			{
				return mRawData.size() / getTypeSize();
			}
		}
	}
}