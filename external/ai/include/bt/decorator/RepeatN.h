#pragma once
#include "../../Dll.h"
#include "../Node.h"

namespace ai {
	namespace bt {

		class RepeatN : public Decorator {
		public:
			RepeatN(int amount_of_repitions) : m_Repitions(amount_of_repitions){}
			Status Update();

		private:
			int m_Repitions;
		};
	} // namespace BT
} // namespace AI