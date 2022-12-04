#pragma once
#include <array>
#include <vector>
#include "engine/Texture.h"

class Tile {
public:
	Tile(texture::TextureData spritesheet);
	~Tile();

	void Draw();

public:
	texture::TextureData m_TextureData;
	SDL_Rect m_Destination;
	SDL_Point m_Position;
};

class Tilemap {
public:
	Tilemap();
	~Tilemap();

	void Initialize(const char* filename, int src_tile_size);
	void Draw();

public:
	std::array<std::array<int, 48>, 27 > MAP_DATA;
	std::vector<Tile> m_Tiles;
	texture::TextureData m_TextureData;	
	SDL_Rect m_Destination;
};