#pragma once
#include <SDL.h> 
#include <pathfinding/Algorithms.h>
#include "Globals.h"
#include "Texture.h"
#include "../Entity.h"

namespace pathing {
	class Node : public Entity {
	public:
		Node() : Entity::Entity() {}

	public:
		SDL_FPoint m_Position;
		SDL_Rect m_Destination;
	#ifdef LOGGING
		void Draw();
		texture::TextureData m_TextureData;
	#endif // LOGGING
	};

	enum class Algo {
		A_Star = 0,
		BFS,
		DFS,
		GBFS,
		DLS,
		IDDFS
	};

	bool Initialize();
	void UnInitialize();

	std::vector<Vector2> CreatePath(Vector2 start_node, Vector2 end_node,
									Algo algorithm = Algo::A_Star,
									ai::path::Obstacle layer = ai::path::Obstacle::None);
	void Reset();
	void SetObstacle(int x, int y, ai::path::Obstacle value);
	void UpdateAi();
	std::vector<Node>& GetMap();

#ifdef LOGGING
	void DebugPaths(globals::Vector& tilemap_dimensions, globals::Vector tile_size);
	void Input();
	void Draw();
#endif // LOGGING
} // namespace PATHING