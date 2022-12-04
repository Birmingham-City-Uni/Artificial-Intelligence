#include "Cooldown.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include "../engine/Font.h"

#define TILE_SIZE 48
#define FPO 8	// Foreground Position Offset
#define FSO 16	// Foreground Size Offset
#define TXO 6	// Text X Position Offset
#define TYO 4	// Text Y Position Offset

void Cooldown::Start()
{
	m_IsCountingDown = true;
}

int Cooldown::GetIndex()
{
	int index = 0;
	if (m_Timer > 10) {
		index += 10 * 10;
		index += m_Timer - 10;
	}
	else {
		index = m_Timer * 10;
	}
	return index;
}

void Cooldown::Initialize(SDL_Point position, int timer)
{
	m_IsCountingDown = false;

	m_Background.Initialize("ui_backdrop.png");
	m_Background.m_Destination = { position.x,position.y,TILE_SIZE,TILE_SIZE };

	m_Foreground.Initialize("ui_foredrop.png");
	m_Foreground.m_Destination = { position.x + FPO,position.y + FPO,TILE_SIZE - FSO,TILE_SIZE - FSO };

	m_Text.Initalize("2");
	
	m_Distance = 100.f;
	m_Timer = timer;
	m_Cooldown = timer;

	auto amount_of_index = GetIndex();
	m_Numbers = { Uint64(amount_of_index), Text() };
	for (int i = 0; i < amount_of_index; i++)
	{
		auto num = std::to_string(float(i) / 10.f);
		num.resize(3);
		if (i > 99){
			num = std::to_string(float(i-90));
			num.resize(2);
		}
		m_Numbers[i].Initalize(num.c_str());
	}	
}

void Cooldown::Update(const float delta_time)
{
	if (m_IsCountingDown) {
		m_Timer = std::clamp(m_Timer -= delta_time, 0.f, m_Cooldown);
		m_Foreground.m_Destination.h = (48/4*3) * ((m_Timer / m_Cooldown));

		int indexs = GetIndex();
		m_Text = m_Numbers[indexs];
		m_Text.m_Dimensions.x = m_Background.m_Destination.x - TXO + (TILE_SIZE - m_Text.m_Dimensions.w / 2) / 2;
		m_Text.m_Dimensions.y = m_Background.m_Destination.y - TYO + (TILE_SIZE - m_Text.m_Dimensions.h / 2) / 2;

		if (m_Timer <= 0.f) {
#ifdef LOGGING
			std::cout << "Cooldown!\n";
#endif // LOGGING
			m_Timer = m_Cooldown;
			m_IsCountingDown = false;
		}
	}
}

void Cooldown::Draw()
{
	m_Background.Draw();
	if (m_IsCountingDown) {
		m_Foreground.Draw();
		m_Text.Draw();
	}
}