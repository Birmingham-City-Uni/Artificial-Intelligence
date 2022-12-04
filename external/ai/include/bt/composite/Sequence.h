#pragma once
#include "../../Dll.h"
#include "../Node.h"

namespace ai {
	namespace bt {

		class Sequence : public CompositeNode {
		public:
			Sequence() {}
			Status Update();
		};
	} // namespace BT
} // namespace AI