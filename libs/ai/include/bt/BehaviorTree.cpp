#include "BehaviorTree.h"

namespace ai {
	namespace bt {

		BtPtr CreateBt(){
			return std::make_shared<BehaviourTree>();
		}

	} // namespace bt
} // namespace ai