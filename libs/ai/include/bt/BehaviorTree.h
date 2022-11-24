#pragma once
#include <memory>
#include "../Dll.h"
#include "Node.h"

namespace ai {
	namespace bt {

		class BehaviourTree;
		typedef std::shared_ptr<BehaviourTree> BtPtr;

		class BehaviourTree {
		public:
			BehaviourTree() {}

			void Update() { root.Update(); }
			void Pause() {}
			void Stop() {}

			// DEBUGGING
			void SetRoot(Node n) { root = n; }
			Node GetRoot() { return root; }

		private:
			Node root;
		};

		extern "C++" AI_API BtPtr CreateBt();
	} // namespace BT
} // namespace AI
