#include "UniversumLib/model/MoveableNode.h"
#include "UniversumLib/type/NodeType.h"

namespace UniLib {
	namespace model {

		MoveableNode::MoveableNode(Node* parent /* = NULL */, const DRVector3& position /* = DRVector3(0.0f) */)
			: Node(parent), mPosition(position)
		{
			mType |= NodeType::MOVEABLE;
		}

		void MoveableNode::calculateMatrix()
		{
			mMatrix = mPosition.calculateMatrix(mMatrix) * mRotation.calculateMatrix();
			if(mParent && magic_enum::enum_integer(mParent->getType() & NodeType::MOVEABLE) != 0) {
				MoveableNode* parent = dynamic_cast<MoveableNode*>(mParent);
				mMatrix *= parent->getMatrix();
			}
		}

		DRReturn MoveableNode::move(float timeSinceLastFrame)
		{
			calculateMatrix();
			return DR_OK;
		}
	}
}