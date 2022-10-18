#include "Nodemap.h"
#include "Renderer.h"
#include "Globals.h"
#include "../Clock.h"

#ifdef LOGGING
#include "Input.h"
#endif // LOGGING

namespace PATHING {
	namespace {
		extern std::vector<AI::PATH::NodePtr> g_NodePtrs{};
		extern std::vector<Node> g_Nodes{};
		extern std::vector<AI::PATH::Vector> g_SolutionNodes{};
		extern std::vector<SDL_Point> g_StartNodes{};
		extern std::vector<SDL_Point> g_EndNodes{};

#ifdef LOGGING
		bool g_DebugActivate = false;
		Texture::TextureData g_DebugTextureData;
		Texture::TextureData g_DebugTextureExploredData;
		Texture::TextureData g_DebugTextureStartData;
		Texture::TextureData g_DebugTextureEndData;
		Texture::TextureData g_DebugObstacle;
#endif // LOGGING
	}

	std::vector<Node>& GetMap(){
		return g_Nodes;
	}

	void Node::Draw()
	{
		SDL_RenderCopy(Renderer::GetRenderer(), m_TextureData.m_Texture, &m_TextureData.m_Source, &m_Destination);
	}

	bool Initialize()
	{
		g_DebugTextureData = Texture::LoadDebugTexture({ 100,100,100,255 }, { 32,32 });
		g_DebugTextureExploredData = Texture::LoadDebugTexture({ 255,255,255,255 }, { 32,32 });
		g_DebugTextureStartData = Texture::LoadDebugTexture({ 0,255,0,255 }, { 32,32 });
		g_DebugTextureEndData = Texture::LoadDebugTexture({ 0,0,255,255 }, { 32,32 });
		g_DebugObstacle = Texture::LoadDebugTexture({ 255,0,0,255 }, { 32,32 });

		auto tilemap_dimensions = Globals::GetTileMapDimensions();
		auto tile_size = Globals::GetTileDimensions();

		g_NodePtrs.reserve(tilemap_dimensions.w * tilemap_dimensions.h);
		g_Nodes.reserve(tilemap_dimensions.w * tilemap_dimensions.h);
		g_SolutionNodes.reserve(tilemap_dimensions.w * tilemap_dimensions.h);

		g_NodePtrs = AI::PATH::CreateNodeMap(tilemap_dimensions.w, tilemap_dimensions.h)->GetMap();
		for (int y = 0; y < tilemap_dimensions.h; y++)
		{
			for (int x = 0; x < tilemap_dimensions.w; x++)
			{
				Node node;
				node.m_TextureData = g_DebugTextureData;
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
		SDL_DestroyTexture(g_DebugTextureData.m_Texture);
		SDL_DestroyTexture(g_DebugTextureExploredData.m_Texture);
		SDL_DestroyTexture(g_DebugTextureStartData.m_Texture);
		SDL_DestroyTexture(g_DebugTextureEndData.m_Texture);
		SDL_DestroyTexture(g_DebugObstacle.m_Texture);
#endif // LOGGING
	}

	void Update()
	{
		g_SolutionNodes.clear();
		g_StartNodes.clear();
		g_EndNodes.clear();
	}

	void Reset()
	{
		auto tilemap_dimensions = Globals::GetTileMapDimensions();
		for (int y = 0; y < tilemap_dimensions.h; y++)
		{
			for (int x = 0; x < tilemap_dimensions.w; x++)
			{
				g_NodePtrs.at(x + (y * tilemap_dimensions.w))->SetObstacle(false);
			}
		}
	}

	void SetObstacle(int x, int y, bool value)
	{
		auto tilemap_dimensions = Globals::GetTileMapDimensions();
		g_NodePtrs.at(x + (y * tilemap_dimensions.w))->SetObstacle(value);
	}

	void CreatePath(SDL_Point start, SDL_Point end, Algo algorithm)
	{
		auto tilemap_dimensions = Globals::GetTileMapDimensions();

		AI::PATH::NodePtr start_node = g_NodePtrs.at(start.x + (start.y * tilemap_dimensions.w));
		AI::PATH::NodePtr end_node = g_NodePtrs.at(end.x + (end.y * tilemap_dimensions.w));
		std::vector<AI::PATH::Vector> solution_path;
		switch (algorithm)
		{
		case PATHING::Algo::A_Star:
			solution_path = AI::PATH::A_Star(g_NodePtrs, start_node, end_node);
			break;
		case PATHING::Algo::BFS:
			solution_path = AI::PATH::BFS(g_NodePtrs, start_node, end_node);
			break;
		case PATHING::Algo::DFS:
			solution_path = AI::PATH::DFS(g_NodePtrs, start_node, end_node);
			break;
		default:
			break;
		} 
#ifdef LOGGING
		g_SolutionNodes.insert(std::end(g_SolutionNodes), std::begin(solution_path), std::end(solution_path));
		g_StartNodes.emplace_back(start);
		g_EndNodes.emplace_back(end);
		DebugPaths(tilemap_dimensions, Globals::GetTileDimensions());
#endif // LOGGING
	}

	void DebugPaths(Globals::Vector& tilemap_dimensions, Globals::Vector tile_size)
	{
		for (int y = 0; y < tilemap_dimensions.h; y++)
		{
			for (int x = 0; x < tilemap_dimensions.w; x++)
			{
				g_Nodes[x + (y * tilemap_dimensions.w)].m_TextureData = g_NodePtrs.at(x + (y * tilemap_dimensions.w))->IsObstacle() ? g_DebugObstacle : g_DebugTextureData;
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
		if (Input::GetKeyUp(SDL_SCANCODE_F2)) {
			g_DebugActivate = !g_DebugActivate;
			Input::SetKeyUp(SDL_SCANCODE_F2, false);
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
} // namespace PATHING