#pragma once
#include "../../Dll.h"
#include "../Node.h"

namespace ai {
	namespace bt {

		class Inverter : public Decorator {
		public:
			Inverter() {}
			Status Update();
		};
	} // namespace BT
} // namespace AI
