#pragma once
#include "../../Dll.h"
#include "../Node.h"

namespace ai {
	namespace bt {
		
		class Selector : public CompositeNode {
		public:
			Selector() {}
			Status Update();
		};
	} // namespace BT
} // namespace AI