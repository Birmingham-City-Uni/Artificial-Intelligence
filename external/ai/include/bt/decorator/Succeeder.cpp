#include "Succeeder.h"

namespace ai {
	namespace bt {

		Status Succeeder::Update() {
			m_Child.Update();
			return Status::Success;
		}
	} // namespace BT
} // namespace AI

