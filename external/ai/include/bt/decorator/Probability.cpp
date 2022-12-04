#include "Probability.h"
#include <random>

namespace ai {
	namespace bt {

		Status Probability::Update() {
			std::random_device dev;
			std::mt19937 rng(dev());
			std::uniform_int_distribution<std::mt19937::result_type> distribution(0, 99);

			if (distribution(rng) < m_Probability) {
				return Status::Success;
			}
			return Status::Failure;
		}
	} // namespace BT
} // namespace AI