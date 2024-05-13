#include "UniversumLib/manager/InstancingBlocks.h"


namespace UniLib {
	namespace manager {

		InstancingBlocks::InstancingBlocks()
		{

		}

		InstancingBlocks::~InstancingBlocks()
		{

		}

		InstancingBlocks* InstancingBlocks::getInstance()
		{
			static InstancingBlocks one;
			return &one;
		}

		void InstancingBlocks::clearEmptyGeometrieBlocks()
		{
			for(auto it = mGeometrieBlocks.begin(); it != mGeometrieBlocks.end(); it++) {
				if(it->second->getGeometrieBlockCount() == 0) {
					it = mGeometrieBlocks.erase(it);
				}
			}
		}

		std::shared_ptr<view::block::GeometrieBlock> InstancingBlocks::findGeometrieBlock(HASH id)
		{
			auto it = mGeometrieBlocks.find(id);
			if(it != mGeometrieBlocks.end()) return it->second;
			return nullptr;
		}
	}
}