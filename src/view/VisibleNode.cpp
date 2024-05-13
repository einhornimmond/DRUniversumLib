#include "UniversumLib/view/VisibleNode.h"
#include "UniversumLib/type/NodeType.h"

namespace UniLib {
	namespace view {
		VisibleNode::VisibleNode(Node* parent /* = NULL */, const DRVector3& position /* = DRVector3(0.0f) */)
			:MoveableNode(parent, position)
		{
			mType |= NodeType::VISIBLE;
		}
	}
}