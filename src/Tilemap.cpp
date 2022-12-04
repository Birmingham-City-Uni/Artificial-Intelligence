#include "Tilemap.h"
#include "engine/Renderer.h"
#include "engine/Globals.h"
#include "Dll.h"
#include <algorithm>

Tile::Tile(texture::TextureData spritesheet)
{
	m_TextureData = spritesheet;
	m_Destination = { 0,0,0,0 };
}

Tile::~Tile()
{

}

void Tile::Draw()
{
	SDL_RenderCopy(renderer::GetRenderer(), m_TextureData.m_Texture, &m_TextureData.m_Source, &m_Destination);
}

//	TODO; @RyanWestwood - Make this read in from a file or assign the array manually
Tilemap::Tilemap()
{
	auto tilemap_dimensions = globals::GetTileMapDimensions();
	for (int y = 0; y < tilemap_dimensions.h; y++)
	{
		for (int x = 0; x < tilemap_dimensions.w; x++)
		{
			MAP_DATA[y][x] = (1) + (4 * 32); // x = 0-31, y = 0-31
		}
	}
}

Tilemap::~Tilemap()
{
	if (m_TextureData.m_Texture) SDL_DestroyTexture(m_TextureData.m_Texture);
}

void Tilemap::Initialize(const char* filename, int src_tile_size)
{
	auto texture = texture::LoadTexture(filename);
	m_TextureData.m_Texture = texture.m_Texture;
	m_TextureData.m_Source = texture.m_Source;
	m_Destination = { 0,0,32,32 };

	auto spritesheet_column = m_TextureData.m_Source.w / src_tile_size;
	auto spritesheet_row = m_TextureData.m_Source.h / src_tile_size;
	auto tilemap_dimensions = globals::GetTileMapDimensions();

	auto tile_size = globals::GetTileDimensions();
	int tile_width = tile_size.w;
	int tile_height = tile_size.h;

	for (int y = 0; y < tilemap_dimensions.h; y++)
	{
		for (int x = 0; x < tilemap_dimensions.w; x++)
		{
			Tile tile = { m_TextureData };
			tile.m_Destination = { tile_width * x, tile_height * y, tile_width, tile_height };
			tile.m_TextureData.m_Source = { (MAP_DATA[y][x] % spritesheet_column) * src_tile_size, (MAP_DATA[y][x] / spritesheet_row) * src_tile_size, src_tile_size, src_tile_size };
			tile.m_Position = { x,y };
			m_Tiles.push_back(tile);
		}
	}
#ifdef LOGGING
	std::cout << "Loading tiles: " << spritesheet_row * spritesheet_column << "\n";
#endif // LOGGING
}

void Tilemap::Draw()
{
	for (auto& tile : m_Tiles) {
		tile.Draw();
	}
//#ifdef LOGGING
//	if (m_DebugActivate) {
//		for (auto& tile : m_DebugTiles) {
//			tile.Draw();
//		}
//	}
//#endif // LOGGING
}
