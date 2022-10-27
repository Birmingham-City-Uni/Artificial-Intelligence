#include "RepeatUntilFail.h"

namespace AI {
	namespace BT {

		Status RepeatUntilFail::Update() {
			while (true) {
				Status result = m_Child.Update();

				if (result == Status::Failure) {
					return Status::Success;
				}
			}
		}
	} // namespace BT
} // namespace AI
