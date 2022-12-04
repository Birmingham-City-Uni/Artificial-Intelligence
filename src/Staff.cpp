#include "Staff.h"
#include <algorithm>

constexpr float SWING_SPEED = 512.f;
constexpr float SWING_ROTATION = 90.f;

Staff::Staff()
{
	m_Cooldown = 2.f;
	m_Timer = nullptr;
	m_Rotation = 0.f;
	m_Center = { 12,40 };
	m_Action = false;
	m_Flip = SDL_FLIP_NONE;
}

void Staff::Initialize(const char* filename, std::shared_ptr<float> timer)
{
#ifdef LOGGING
	std::cout << "Staff initialize\n";
#endif // LOGGING
	m_Sprite.Initialize("tilemap.png");
	m_Sprite.m_Source = { 336, 144,16,32 };
	m_Sprite.m_Destination = { 128,128,16,32 };
	m_Timer = timer;
	m_Cooldown = 2.f;
}

void Staff::Update(const float& delta_time, const SDL_FPoint position)
{
	m_Sprite.m_Destination.x = position.x + 10;
	m_Sprite.m_Destination.y = position.y + 10;

	if (m_Action) {
		m_Rotation = std::clamp(m_Rotation + ((!m_Flip << 1) - 1) * delta_time * SWING_SPEED, -SWING_ROTATION, SWING_ROTATION);
		if (m_Rotation >= SWING_ROTATION || m_Rotation <= -SWING_ROTATION) {
			m_Action = false;
			m_Rotation = 0.f;
		}
	}
}

void Staff::Draw(const SDL_RendererFlip& flip /*= SDL_FLIP_NONE*/)
{
	m_Flip = flip;
	m_Sprite.Draw(m_Flip, m_Rotation, m_Center);
}

void Staff::Fire()
{
		if (*m_Timer > m_Cooldown) {
		m_Rotation = 0.f;
		m_Action = true;
		*m_Timer = 0.f;
	}
}