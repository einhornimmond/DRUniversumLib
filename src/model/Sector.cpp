#include "UniversumLib/model/Sector.h"
#include "UniversumLib/model/SectorID.h"
#include "UniversumLib/type/NodeType.h"

#include "magic_enum/magic_enum.hpp"

namespace UniLib {
	namespace model {


		// constructor
		Sector::Sector(Node* parent, SectorID* id, view::Sector* sektorView /*= NULL*/)
			: Node(parent),mSectorView(sektorView), mID(id)
		{
			mType |= magic_enum::enum_integer(NodeType::NODE);
			if(mSectorView) mSectorView->setSectorModel(this);
		}

		// ---------------------------------------------------------------------------

		Sector::~Sector()
		{
		}


	};
};

