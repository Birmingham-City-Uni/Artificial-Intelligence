#pragma once
#include "../Dll.h"
#include <vector>

namespace ai {
	namespace bt {

		enum class Status {
			Success = 0,
			Failure,
			Running,
			Error
		};

		class Node {
		public:
			Node() {}
			Status Update() { return Status::Error; }
		};

		class Decorator : public Node {
		public:
			Decorator() {}
			Status Update() {}

		protected:
			Node m_Child;
		};

		class CompositeNode : public Node {
		public:
			CompositeNode() {}
			void AddChild(Node child) { m_Children.push_back(child); }

		protected:
			std::vector<Node> m_Children;
		};
	} // namespace BT
} // namespace AI