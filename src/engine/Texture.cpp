#include "Texture.h"
#include <string.h>
#include "Renderer.h"
#include "Globals.h"

namespace texture {

	namespace {
		std::string g_TextureDirectory = "Not yet initialized!\n";
	}

	bool Initialize()
	{
		g_TextureDirectory = globals::GetAssetDirectory();
		g_TextureDirectory += "textures/";
		return true;
	}

	TextureData LoadTexture(const char* filename)
	{
#ifdef LOGGING
		std::cout << "Loading texture: " << filename << "\n";
#endif // LOGGING
		try {
			SDL_Surface* surface = IMG_Load((g_TextureDirectory + std::string(filename)).c_str());
			if (surface == nullptr) throw TextureError();
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer::GetRenderer(), surface);
			if (texture == nullptr) throw TextureError();
			SDL_Rect source = { 0,0,surface->w,surface->h };
			SDL_FreeSurface(surface);
			return { texture, source };
		}
		catch (std::exception& e) {
			std::cout << "An exception was thrown." << "\n";
			std::cout << "\t" << e.what() << "\t" << IMG_GetError() << "\n";
			return {};
		}
	}

	TextureData LoadSolidColourTexture(SDL_Colour colour, SDL_Point dimensions)
	{
		Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
#endif
#ifdef LOGGING
		std::cout << "Loading debug texture: " << "\n";
#endif // LOGGING
		try {
			SDL_Surface* surface = SDL_CreateRGBSurface(0, 32, 32, 32, rmask, gmask, bmask, amask);
			SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, colour.r, colour.g, colour.b, colour.a));
			if (surface == nullptr) throw TextureError();
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer::GetRenderer(), surface);
			if (texture == nullptr) throw TextureError();
			SDL_Rect source = { 0,0,surface->w,surface->h };
			SDL_FreeSurface(surface);
			return { texture, source };
		}
		catch (std::exception& e) {
			std::cout << "An exception was thrown." << "\n";
			std::cout << "\t" << e.what() << "\t" << IMG_GetError() << "\n";
			return {};
		}
	}

	void Draw(SDL_Texture* texture, const SDL_Rect& source, const SDL_Rect& destination)
	{
		SDL_RenderCopy(renderer::GetRenderer(), texture, &source, &destination);
	}
} // namespace Texture

Sprite::Sprite()
{
	m_Texture = nullptr;
	m_Source = { 0,0,0,0 };
	m_Destination = { 0,0,0,0 };
}

Sprite::~Sprite()
{
	if(m_Texture) SDL_DestroyTexture(m_Texture);
}

void Sprite::Initialize(const char* filename)
{
	auto texture = texture::LoadTexture(filename);
	m_Texture = texture.m_Texture;
	m_Source = texture.m_Source;
	m_Destination = { 0,0,32,32 };
}

void Sprite::Initialize(SDL_Colour colour, SDL_Point source_dimensions)
{
	auto texture = texture::LoadSolidColourTexture(colour, source_dimensions);
	m_Texture = texture.m_Texture;
	m_Source = texture.m_Source;
	m_Destination = { 0,0,32,32 };
}

void Sprite::Draw(const SDL_RendererFlip& flip, const float& angle, const SDL_Point& point)
{
	SDL_RenderCopyEx(renderer::GetRenderer(), m_Texture, &m_Source, &m_Destination, angle, &point, flip);
}