#pragma once
#include <vector>
#include "../engine/Font.h"
#include "../engine/Texture.h"

class Cooldown {
public:
	Cooldown() {}

	int GetIndex();
	void Initialize(SDL_Point position, int timer);
	void Start();
	
	void Update(const float delta_time);
	void Draw();

public:
	Sprite m_Background;
	Sprite m_Foreground;
	Text m_Text;
	std::vector<Text> m_Numbers;
	float m_Distance;
	float m_Timer;
	float m_Cooldown;
	std::string m_Message;
	bool m_IsCountingDown;
};