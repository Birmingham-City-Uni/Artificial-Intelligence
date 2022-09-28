#pragma once
#include <iostream>
#include <SDL_ttf.h>

namespace Font {
	class FontError : public std::exception {
	public:
		const char* what() const throw() { return "Font Loading Error!\n"; }
	};

	bool InitializeFont();
	void UnInitializeFont();

	struct FontData {
		TTF_Font* m_Font;
		SDL_Texture* m_Texture;
		SDL_Rect m_Dimensions;
	};

	FontData LoadFont(const char* filename, int fontsize, const char* message, const SDL_Color& color, const SDL_Point& position);
	void Draw(SDL_Texture* texture, const SDL_Rect& dimensions);
}

class Text {
public:
	Text();

	void Initalize(const char* filename, const char* message);
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