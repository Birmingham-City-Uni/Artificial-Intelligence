#pragma once
#include <iostream>
#include <SDL_image.h>

namespace Texture {
	class TextureError : public std::exception {
	public:
		const char* what() const throw() { return "Texture Loading Error!"; }
	};

	SDL_Texture* LoadTexture(const char* filename);
	SDL_Rect LoadTextureRect(const char* filename);
	void Draw(SDL_Texture* texture, const SDL_Rect& src, const SDL_Rect& dest);
}

class Sprite {
public: 
	Sprite();

	void Initialize(const char* filename);
	void Draw();

public:
	SDL_Texture* m_Texture;
	SDL_Rect m_Source;
	SDL_Rect m_Destination;
};