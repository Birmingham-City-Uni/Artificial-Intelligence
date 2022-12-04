#pragma once
#include "../../Dll.h"
#include "../Node.h"

namespace ai {
	namespace bt {

		class RepeatUntilSuccess : public Decorator {
		public:
			RepeatUntilSuccess() {}
			Status Update();
		};
	} // namespace BT
} // namespace AI