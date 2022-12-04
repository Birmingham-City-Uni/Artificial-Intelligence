#include "Inverter.h"

namespace ai {
	namespace bt {

		Status Inverter::Update() {
			Status result = m_Child.Update();
			if (result == Status::Success) {
				return Status::Failure;
			}
			else if (result == Status::Failure) {
				return Status::Success;
			}
			return result;
		}
	} // namespace BT
} // namespace AI

