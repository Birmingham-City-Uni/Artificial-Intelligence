#pragma once
#include <memory>
#include <vector>
#include "../Dll.h"
#include "../math/Vector2.h"

namespace ai {
	namespace path{

		class Node;
		typedef std::shared_ptr<Node> NodePtr;

		struct Costs {
			float m_FromCost, m_ToCost, m_TotalCost;
		};

		enum Obstacle : uint8_t {
			None			= 0x00,
			Player			= 0x01,
			Ad				= 0x02,
			Boss			= 0x04,
			ToxicPool		= 0x08,
			Placeholder		= 0x10,
			Placeholder1	= 0x20,
			Placeholder2	= 0x40,
			Placeholder3	= 0x80,
			All				= 0xFF
		};

		class Node {
		public:
			Node();
			bool IsObstacle(Obstacle layer) { return layer & m_ObstacleLayer; }
			bool IsVisited() { return m_Visited; }
			Vector2 GetPosition() { return m_Position; }
			Costs GetCosts() { return m_Costs; }
			NodePtr GetParent() { return m_Parent; }
			std::vector<NodePtr> GetNeighbours() { return m_Neighbours; }

			void SetObstacle(Obstacle obstacle) { m_ObstacleLayer = obstacle; }
			void SetVisited(bool visited) { m_Visited = visited; }
			void SetPosition(Vector2 position) { m_Position = position; }
			void SetCosts(Costs costs) { m_Costs = costs; }
			void SetParent(NodePtr parent) { m_Parent = parent; }
			void AddNeighbours(NodePtr neighbours) { m_Neighbours.push_back(neighbours); }
		public:
			Costs m_Costs; // TODO @RyanWestwood: Change this to private and adjust the algorithms!
		private:
			Vector2 m_Position;
			bool m_Visited;
			Obstacle m_ObstacleLayer;
			NodePtr m_Parent;
			std::vector<NodePtr> m_Neighbours;
		};

		extern "C++" AI_API std::vector<NodePtr> CreateNodeMap(int, int);
		void ResetNodeMap(std::vector<NodePtr> nodes);
	} // namespace PATH
} // namespace AI