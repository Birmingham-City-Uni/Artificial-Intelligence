#pragma once
#include "../engine/Texture.h"

class HealthBar{
public:
	HealthBar();
	void Initialize(SDL_Rect position, int border);

	void Draw();
	void ChangeHealth(int health_percentage);
private:
	Sprite m_Foreground;
	Sprite m_Background;
	int m_Health;
	int m_Border;
};