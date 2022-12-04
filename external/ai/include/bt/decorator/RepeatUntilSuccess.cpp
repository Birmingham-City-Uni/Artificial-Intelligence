#include "RepeatUntilSuccess.h"

namespace ai {
	namespace bt {

		Status RepeatUntilSuccess::Update() {
			while (true) {
				Status result = m_Child.Update();
				if (result == Status::Success) {
					return Status::Success;
				}
			}
		}
	} // namespace BT
} // namespace AI