#include "UniversumLib/model/Sector.h"
#include "UniversumLib/model/SectorID.h"
#include "UniversumLib/type/NodeType.h"

namespace UniLib {
	namespace model {


		// constructor
		Sector::Sector(Node* parent, SectorID* id, view::Sector* sektorView /*= NULL*/)
			: Node(parent),mSectorView(sektorView), mID(id)
		{
			mType |= NodeType::NODE;
			if(mSectorView) mSectorView->setSectorModel(this);
		}

		// ---------------------------------------------------------------------------

		Sector::~Sector()
		{
		}


	};
};

