#include "Font.h"
#include <string.h>
#include "Renderer.h"
#include "Globals.h"

namespace font {

	namespace {
		std::string g_FontDirectory = "Not yet initialized!\n";
		FontData g_Font;
	}

	bool InitializeFont()
	{
		g_FontDirectory = globals::GetAssetDirectory();
		g_FontDirectory += "font/";
		if (TTF_Init() < 0) {
			std::cout << "SDL_TTF could not initialize! SDL_TTF error: " << TTF_GetError() << "\n";
			return false;
		}
#ifdef LOGGING
		std::cout << "Font Initialized!\n";
#endif // LOGGING
		return true;
	}

	void InitializeDefaultFont() {
		g_Font = LoadFont("font.ttf", 18, "Default", { 255,255,255,255 }, { 0,0 });
	}

	FontData GetDefaultFont() {
		return g_Font;
	}

	void UnInitializeFont()
	{
		TTF_Quit();
	}

	FontData LoadFont(const char* filename, int fontsize, const char* message, const SDL_Color& color, const SDL_Point& position)
	{
#ifdef LOGGING
		std::cout << "Loading font: " << filename << "\n";
#endif // LOGGING
		try {
			TTF_Font* font = TTF_OpenFont((g_FontDirectory + std::string(filename)).c_str(), fontsize);
			if (font == nullptr) throw FontError();
			SDL_Surface* surface = TTF_RenderText_Solid(font, message, color);
			if (surface == nullptr) throw FontError();
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer::GetRenderer(), surface);
			SDL_Rect dimensions = { position.x, position.y, surface->w, surface->h };
			SDL_FreeSurface(surface);
			return { font, texture, dimensions };
		}
		catch (std::exception& e) {
			std::cout << "An exception was thrown." << "\n";
			std::cout << "\t" << e.what() << "\t" << TTF_GetError() << "\n";
			return {};
		}
	}

	FontData UpdateMessage(const char* message, TTF_Font* font, const SDL_Color& color, const SDL_Point& position)
	{
//#ifdef LOGGING
//		std::cout << "Updating font message: " << message<< "\n";
//#endif // LOGGING
		try {
			SDL_Surface* surface = TTF_RenderText_Solid(font, message, color);
			if (surface == nullptr) throw FontError();
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer::GetRenderer(), surface);
			SDL_Rect dimensions = { position.x, position.y, surface->w, surface->h };
			SDL_FreeSurface(surface);
			return {font, texture, dimensions};

		}
		catch (std::exception& e) {
			std::cout << "An exception was thrown." << "\n";
			std::cout << "\t" << e.what() << ": " << "\t" << TTF_GetError();
			return {};
		}
	}

	void Draw(SDL_Texture* texture, const SDL_Rect& dimensions)
	{
		SDL_RenderCopy(renderer::GetRenderer(), texture, 0, &dimensions);
	}
} // namespace Font

Text::Text()
{
	m_Colour = { 255, 255, 255,255 };
	m_Position = { 0,0 };
	m_FontSize = 18;
	m_Dimensions = { 0,0,0,0 };
	m_Message = nullptr;
	m_Font = nullptr;
	m_Texture = nullptr;
}

Text::~Text()
{
	if(m_Texture) SDL_DestroyTexture(m_Texture);
	if(m_Font) TTF_CloseFont(m_Font);
}

void Text::Initalize(const char* filename, const char* message, int font_size)
{
	auto font_data = font::LoadFont(filename, font_size, message, m_Colour, m_Position);
	m_FontSize = font_size;
	m_Message = message;
	m_Font = font_data.m_Font;
	m_Texture = font_data.m_Texture;
	m_Dimensions = font_data.m_Dimensions;
}

void Text::Initalize(const char* message)
{
	auto font_data = font::UpdateMessage(message, font::GetDefaultFont().m_Font, m_Colour, m_Position);
	m_Message = message;
	m_Font = font_data.m_Font;
	m_Texture = font_data.m_Texture;
	m_Dimensions = font_data.m_Dimensions;
}

void Text::UpdateMessage(const char* message)
{
	SDL_DestroyTexture(m_Texture);
	auto updated_message = font::UpdateMessage(message, m_Font, m_Colour, m_Position);
	m_Texture = updated_message.m_Texture;
	m_Dimensions = updated_message.m_Dimensions;
}

void Text::Draw()
{
	font::Draw(m_Texture, m_Dimensions);
}