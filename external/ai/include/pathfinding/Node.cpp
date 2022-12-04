#include "Node.h"

namespace ai {
	namespace path {

		Node::Node()
		{
			m_ObstacleLayer = Obstacle::None;
			m_Visited = false;
			m_Costs = { 0,0,0 };
			m_Position = { 0,0 };
			m_Neighbours;
			m_Parent;
		}

		std::vector<NodePtr> CreateNodeMap(int map_width, int map_height)
		{
			std::vector<NodePtr> map{};
			map.reserve(map_width * map_height);
			for (int y = 0; y < map_height; y++)
			{
				for (int x = 0; x < map_width; x++)
				{
					auto node = std::make_shared<Node>();
					node->SetObstacle(Obstacle::None);
					node->SetVisited(false);
					node->SetPosition({ (float)x, (float)y });
					node->SetParent(nullptr);
					map.push_back(node);
				}
			}

			for (int y = 0; y < map_height; y++)
			{
				for (int x = 0; x < map_width; x++)
				{
					if (y > 0)
						map[y * map_width + x]->AddNeighbours(map[(y - 1) * map_width + (x)]);
					if (y < map_height - 1)
						map[y * map_width + x]->AddNeighbours(map[(y + 1) * map_width + (x)]);
					if (x > 0)
						map[y * map_width + x]->AddNeighbours(map[(y)*map_width + (x - 1)]);
					if (x < map_width - 1)
						map[y * map_width + x]->AddNeighbours(map[(y)*map_width + (x + 1)]);
				}
			}
			return map;
		}

		void ResetNodeMap(std::vector<NodePtr> nodes) {
			for (int x = 0; x < 48; x++)
			{
				for (int y = 0; y < 27; y++)
				{
					nodes[y * 48 + x]->SetCosts({ FLT_MAX, FLT_MAX, FLT_MAX });
					nodes[y * 48 + x]->SetVisited(false);
					nodes[y * 48 + x]->SetParent(nullptr);
				}
			}
		}
	} // namespace PATH
} // namespace AI