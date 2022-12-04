#pragma once
#include "../Dll.h"
#include "../math/Vector2.h"
#include "Node.h"

namespace ai {
	namespace path {

		extern "C++" AI_API std::vector<Vector2> A_Star(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node, Obstacle layer);
		extern "C++" AI_API std::vector<Vector2> BFS(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node, Obstacle layer);
		extern "C++" AI_API std::vector<Vector2> Greedy_BFS(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node, Obstacle layer);
		extern "C++" AI_API std::vector<Vector2> DFS(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node, Obstacle layer);
		extern "C++" AI_API std::vector<Vector2> DLS(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node, Obstacle layer);

		struct DLS_Data {
			NodePtr found;
			bool remaining;
		};
		extern "C++" AI_API std::vector<Vector2> IDDFS_Caller(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node, Obstacle layer, int depth);
		extern "C++" AI_API std::vector<Vector2> DLS_Caller(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node, Obstacle layer, int depth);
	} // namespace PATH
} // namespace AI