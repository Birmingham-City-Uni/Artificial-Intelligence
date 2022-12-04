#include "Selector.h"

namespace ai {
	namespace bt {

		Status Selector::Update() {
			for (auto child : m_Children) {
				if (child.Update() == Status::Success) {
					return Status::Success;
				}
			}
			return Status::Failure;
		}
	} // namespace BT
} // namespace AI