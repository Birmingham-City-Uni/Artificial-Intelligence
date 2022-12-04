#pragma once
#include "../../Dll.h"
#include "../Node.h"

namespace ai {
	namespace bt {

		class RandomSelector : public CompositeNode {
		public:
			RandomSelector() {}
			Status Update();
		};
	} // namespace BT
} // namespace AI