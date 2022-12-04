#include "Pathing.h"
#include "Renderer.h"
#include "Globals.h"
#include "../engine/Clock.h"

#ifdef LOGGING
#include "Input.h"
#endif // LOGGING

namespace pathing {
	namespace {
		extern std::vector<ai::path::NodePtr> g_NodePtrs{};
		extern std::vector<Node> g_Nodes{};
		extern std::vector<Vector2> g_SolutionNodes{};
		extern std::vector<Vector2> g_StartNodes{};
		extern std::vector<Vector2> g_EndNodes{};

		texture::TextureData g_DefaultTexture;
#ifdef LOGGING
		bool g_DebugActivate = false;
		texture::TextureData g_DebugTextureExploredData;
		texture::TextureData g_DebugTextureStartData;
		texture::TextureData g_DebugTextureEndData;
		texture::TextureData g_DebugObstacle;
#endif // LOGGING
	}

	std::vector<Node>& GetMap() {
		return g_Nodes;
	}

#ifdef LOGGING
	void Node::Draw()
	{
		SDL_RenderCopy(renderer::GetRenderer(), m_TextureData.m_Texture, &m_TextureData.m_Source, &m_Destination);
	}
#endif

	bool Initialize()
	{
#ifdef LOGGING
		g_DefaultTexture = texture::LoadSolidColourTexture({ 100,100,100,255 }, { 32,32 });
		g_DebugTextureExploredData = texture::LoadSolidColourTexture({ 255,255,255,255 }, { 32,32 });
		g_DebugTextureStartData = texture::LoadSolidColourTexture({ 0,255,0,255 }, { 32,32 });
		g_DebugTextureEndData = texture::LoadSolidColourTexture({ 0,0,255,255 }, { 32,32 });
		g_DebugObstacle = texture::LoadSolidColourTexture({ 255,0,0,255 }, { 32,32 });
#endif // LOGGING
		auto tilemap_dimensions = globals::GetTileMapDimensions();
		auto tile_size = globals::GetTileDimensions();

		g_NodePtrs.reserve(tilemap_dimensions.w * tilemap_dimensions.h);
		g_Nodes.reserve(tilemap_dimensions.w * tilemap_dimensions.h);
		g_SolutionNodes.reserve(tilemap_dimensions.w * tilemap_dimensions.h);

		g_NodePtrs = ai::path::CreateNodeMap(tilemap_dimensions.w, tilemap_dimensions.h);
		for (int y = 0; y < tilemap_dimensions.h; y++)
		{
			for (int x = 0; x < tilemap_dimensions.w; x++)
			{
				Node node;
#ifdef LOGGING
				node.m_TextureData = g_DefaultTexture;
#endif // LOGGING
				node.m_Position = { float(x),float(y) };
				node.m_Collider = { x * 32 , y * 32,32,32 };
				node.m_Destination = { tile_size.w * x + 8, tile_size.h * y + 8, tile_size.w / 2, tile_size.h / 2 };
				g_Nodes.push_back(node);
			}
		}
		return true;
	}

	void UnInitialize()
	{
#ifdef LOGGING
		SDL_DestroyTexture(g_DefaultTexture.m_Texture);
		SDL_DestroyTexture(g_DebugTextureExploredData.m_Texture);
		SDL_DestroyTexture(g_DebugTextureStartData.m_Texture);
		SDL_DestroyTexture(g_DebugTextureEndData.m_Texture);
		SDL_DestroyTexture(g_DebugObstacle.m_Texture);
#endif // LOGGING
	}

	void UpdateAi()
	{
		g_SolutionNodes.clear();
		g_StartNodes.clear();
		g_EndNodes.clear();
	}

	void Reset()
	{
		auto tilemap_dimensions = globals::GetTileMapDimensions();
		for (int y = 0; y < tilemap_dimensions.h; y++)
		{
			for (int x = 0; x < tilemap_dimensions.w; x++)
			{
				g_NodePtrs.at(x + (y * tilemap_dimensions.w))->SetObstacle(ai::path::Obstacle::None);
			}
		}
	}

	void SetObstacle(int x, int y, ai::path::Obstacle value)
	{
		auto tilemap_dimensions = globals::GetTileMapDimensions();
		g_NodePtrs.at(x + (y * tilemap_dimensions.w))->SetObstacle(value);
	}

	std::vector<Vector2> CreatePath(Vector2 start, Vector2 end, Algo algorithm, ai::path::Obstacle layer)
	{
		auto tilemap_dimensions = globals::GetTileMapDimensions();

		ai::path::NodePtr start_node = g_NodePtrs.at(start.x + (start.y * tilemap_dimensions.w));
		ai::path::NodePtr end_node = g_NodePtrs.at(end.x + (end.y * tilemap_dimensions.w));
		std::vector<Vector2> solution_path;
		switch (algorithm)
		{
		case pathing::Algo::A_Star:
			timer::StartTimer();
			solution_path = ai::path::A_Star(g_NodePtrs, start_node, end_node, layer);
			timer::StopTimer("A_Star");
			break;
		case pathing::Algo::BFS:
			timer::StartTimer();
			solution_path = ai::path::BFS(g_NodePtrs, start_node, end_node, layer);
			timer::StopTimer("BFS");
			break;
		case pathing::Algo::DFS:
			timer::StartTimer();
			solution_path = ai::path::DFS(g_NodePtrs, start_node, end_node, layer);
			timer::StopTimer("DFS");
			break;
		case pathing::Algo::GBFS:
			timer::StartTimer();
			solution_path = ai::path::Greedy_BFS(g_NodePtrs, start_node, end_node, layer);
			timer::StopTimer("Greedy BFS");
			break;
		case pathing::Algo::DLS:
			timer::StartTimer();
			solution_path = ai::path::DLS_Caller(g_NodePtrs, start_node, end_node, layer, 10);
			timer::StopTimer("DLS");
			break;
		case pathing::Algo::IDDFS:
			timer::StartTimer();
			solution_path = ai::path::IDDFS_Caller(g_NodePtrs, start_node, end_node, layer, 25);
			timer::StopTimer("IDDFS");
			break;
		default:
			break;
		} 
#ifdef LOGGING
		g_SolutionNodes.insert(std::end(g_SolutionNodes), std::begin(solution_path), std::end(solution_path));
		g_StartNodes.emplace_back(start);
		g_EndNodes.emplace_back(end);
		DebugPaths(tilemap_dimensions, globals::GetTileDimensions());
#endif // LOGGING
		return solution_path;
	}

#ifdef LOGGING
	void DebugPaths(globals::Vector& tilemap_dimensions, globals::Vector tile_size)
	{
		for (int y = 0; y < tilemap_dimensions.h; y++)
		{
			for (int x = 0; x < tilemap_dimensions.w; x++)
			{
				g_Nodes[x + (y * tilemap_dimensions.w)].m_TextureData = g_NodePtrs.at(x + (y * tilemap_dimensions.w))->IsObstacle(ai::path::Obstacle::All) ? g_DebugObstacle : g_DefaultTexture;
			}
		}
		for(auto& node : g_SolutionNodes){
			g_Nodes.at(node.x + (node.y * tilemap_dimensions.w)).m_TextureData = g_DebugTextureExploredData;
		}
		for(auto& node : g_StartNodes){
			g_Nodes.at(node.x + (node.y * tilemap_dimensions.w)).m_TextureData.m_Texture = g_DebugTextureStartData.m_Texture;
		}
		for (auto& node : g_EndNodes) {
			g_Nodes.at(node.x + (node.y * tilemap_dimensions.w)).m_TextureData.m_Texture = g_DebugTextureEndData.m_Texture;
		}
	}

	void Input()
	{
		if (input::GetKeyUp(SDL_SCANCODE_F2)) {
			g_DebugActivate = !g_DebugActivate;
			input::SetKeyUp(SDL_SCANCODE_F2, false);
		}
	}

	void Draw()
	{
		if (g_DebugActivate) {
			for (auto& node : g_Nodes) {
				node.Draw();
			}
		}
	}
#endif // LOGGING
} // namespace PATHING