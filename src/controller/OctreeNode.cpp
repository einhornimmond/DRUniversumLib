#include "UniversumLib/controller/OctreeNode.h"
#include "UniversumLib/model/SectorID.h"
#include "UniversumLib/type/NodeType.h"

#include "magic_enum/magic_enum.hpp"

namespace UniLib {
	namespace controller {


		OctreeNode::OctreeNode(model::SectorID* id, model::Node* parent /* = NULL */)
			: Sector(parent, id)
		{
			mType |= magic_enum::enum_integer(NodeType::OCTREE);
			memset(mChilds, 0, sizeof(model::Node*) * 8);
		}

		OctreeNode::~OctreeNode()
		{

		}

		DRReturn OctreeNode::move(float timeSinceLastFrame)
		{
			for (int i = 0; i < 8; i++) {
				if (mChilds[i]) mChilds[i]->move(timeSinceLastFrame);
			}
			return DR_OK;
		}
	}
}