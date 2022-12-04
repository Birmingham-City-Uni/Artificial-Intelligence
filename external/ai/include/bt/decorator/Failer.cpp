#include "Failer.h"

namespace ai {
	namespace bt {

		Status Failer::Update() {
			m_Child.Update();
			return Status::Failure;
		}
	} // namespace BT
} // namespace AI