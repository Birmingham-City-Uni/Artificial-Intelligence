#pragma once
#include <iostream>
#include <SDL_ttf.h>

namespace font {
	class FontError : public std::exception {
	public:
		const char* what() const throw() { return "Font Loading Error!\n"; }
	};

	bool InitializeFont();
	void UnInitializeFont();
	void InitializeDefaultFont();

	struct FontData {
		TTF_Font* m_Font;
		SDL_Texture* m_Texture;
		SDL_Rect m_Dimensions;
	};
	FontData GetDefaultFont();

	FontData LoadFont(const char* filename, int fontsize, const char* message, const SDL_Color& color, const SDL_Point& position);
	FontData UpdateMessage(const char* message, TTF_Font* font, const SDL_Color& color, const SDL_Point& position);
	void Draw(SDL_Texture* texture, const SDL_Rect& dimensions);
} // namespace Font

class Text {
public:
	Text();
	~Text();

	void Initalize(const char* filename, const char* message, int font_size = 18);
	void Initalize(const char* message);
	void UpdateMessage(const char* message);
	void Draw();

public:
	SDL_Texture* m_Texture;
	TTF_Font* m_Font;
	SDL_Color m_Colour;
	SDL_Point m_Position;
	SDL_Rect m_Dimensions;
	const char* m_Message;
	int m_FontSize;
};