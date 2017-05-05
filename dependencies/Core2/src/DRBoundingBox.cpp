#include "Core2Main.h"

DRBoundingBox::DRBoundingBox(DRVector2* vertices, u16 vertexCount)
	: mMin(0.0f), mMax(0.0f)
{
	mMin = DRVector2(1000.0f);
	for (int iVertices = 0; iVertices < vertexCount; iVertices++) {
		for (int i = 0; i < 2; i++) {
			mMin.c[i] = min(mMin.c[i], vertices[iVertices].c[i]);
			mMax.c[i] = max(mMax.c[i], vertices[iVertices].c[i]);
		}
	}
}
void DRBoundingBox::expandBy(const DRBoundingBox& otherBoundingBox)
{
	for (int i = 0; i < 2; i++) {
		mMin.c[i] = min(mMin.c[i], otherBoundingBox.mMin.c[i]);
		mMax.c[i] = max(mMax.c[i], otherBoundingBox.mMax.c[i]);
	}
	/*// xmin
	if (otherBoundingBox.mMin.x < mMin.x) mMin.x = otherBoundingBox.mMin.x;
	// xmax
	if (otherBoundingBox.mMax.x > mMax.x) mMax.x = otherBoundingBox.mMax.x;
	// ymin
	if (otherBoundingBox.mMin.y < mMin.y) mMin.y = otherBoundingBox.mMin.y;
	// ymax
	if (otherBoundingBox.mMax.y > mMax.y) mMax.y = otherBoundingBox.mMax.y;
	*/
}

bool DRBoundingBox::intersects(const DRBoundingBox& otherBoundingBox) const
{
	return (max(mMin.x, otherBoundingBox.mMin.x) <= min(mMax.x, otherBoundingBox.mMax.x) &&
		    max(mMin.y, otherBoundingBox.mMin.y) <= min(mMax.y, otherBoundingBox.mMax.y));
}
bool DRBoundingBox::inside(const DRBoundingBox& otherBoundingBox) const
{
	return otherBoundingBox.mMin.x >= mMin.x && otherBoundingBox.mMax.x <= mMax.x &&
		   otherBoundingBox.mMin.y >= mMin.y && otherBoundingBox.mMax.y <= mMax.y;
}
