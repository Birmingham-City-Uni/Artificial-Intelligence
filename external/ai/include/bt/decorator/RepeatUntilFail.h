#pragma once
#include "../../Dll.h"
#include "../Node.h"

namespace ai {
	namespace bt {

		class RepeatUntilFail : public Decorator {
		public:
			RepeatUntilFail() {}
			Status Update();
		};
	} // namespace BT
} // namespace AI