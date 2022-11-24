#pragma once
#include "../Dll.h"
#include <vector>

// DEBUGGING
#include <iostream>

namespace ai {
	namespace bt {

		enum class Status {
			Success = 0,
			Failure,
			Running,
			Error
		};

		class INode {
		public:
			virtual Status Update() = 0;
		};

		class Node {
		public: 
			Status Update() { 
				// DEBUGGING
				std::cout << "Node!\n";
				return Status::Error; 
			}
		};

		class AI_API NodeWrapper : public Node{
		public:
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