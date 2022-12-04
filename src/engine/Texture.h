#pragma once
#include <iostream>
#include <SDL_image.h>

namespace texture {
	class TextureError : public std::exception {
	public:
		const char* what() const throw() { return "Texture Loading Error!"; }
	};

	struct TextureData {
		SDL_Texture* m_Texture;
		SDL_Rect m_Source;
	};

	bool Initialize();
	TextureData LoadTexture(const char* filename);
	TextureData LoadSolidColourTexture(SDL_Colour colour, SDL_Point dimensions);
	void Draw(SDL_Texture* texture, const SDL_Rect& source, const SDL_Rect& destination);
} // namespace Texture

class Sprite {
public: 
	Sprite();
	~Sprite();

	void Initialize(const char* filename);
	void Initialize(SDL_Colour colour, SDL_Point source_dimensions);
	void Draw(const SDL_RendererFlip& flip = SDL_FLIP_NONE, const float& angle = 0.f, const SDL_Point& point = {});

public:
	SDL_Texture* m_Texture;
	SDL_Rect m_Source;
	SDL_Rect m_Destination;
};