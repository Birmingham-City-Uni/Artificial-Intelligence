#pragma once
#include "../../Dll.h"
#include "../Node.h"

namespace ai {
	namespace bt {

		class Succeeder : public Decorator {
		public:
			Succeeder() {}
			Status Update();
		};
	} // namespace BT
} // namespace AI