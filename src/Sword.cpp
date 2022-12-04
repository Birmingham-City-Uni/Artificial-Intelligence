#include "Sword.h"
#include <iostream>
#include <algorithm>

constexpr float SWING_SPEED = 512.f;
constexpr float SWING_ROTATION = 90.f;

Sword::Sword()
{
	m_Cooldown = 2.f;
	m_Timer = nullptr;
	m_Rotation = 0;
	m_Center = { 12,40 };
	m_Action = false;
	m_FireAction = false;
	m_Flip = SDL_FLIP_NONE;
}

void Sword::Initialize(const char* filename, std::shared_ptr<float> timer, std::shared_ptr<globals::Direction> facing) {
#ifdef LOGGING
	std::cout << "Sword initialize\n";
#endif // LOGGING
	m_Sprite.Initialize("tilemap.png");
	m_Sprite.m_Source = { 336,16,16,32 };
	m_Sprite.m_Destination = { 128,128,24,48 };
	m_Timer = timer;
	m_Cooldown = 2.f;
	m_Facing = facing;

	m_Projectile.Initialize(3);
}

void Sword::Update(const float& delta_time, const SDL_FPoint position)
{
	m_Sprite.m_Destination.x = position.x;
	m_Sprite.m_Destination.y = position.y;
	int side = (!m_Flip << 1) - 1;
	int side_flipped = side * -1;

	if (m_Action) {
		m_Rotation = std::clamp(m_Rotation + side * delta_time * SWING_SPEED, -SWING_ROTATION, SWING_ROTATION);
		if (m_Rotation >= SWING_ROTATION || m_Rotation <= -SWING_ROTATION) {
			m_Action = false;
			m_Rotation = 0.f;
		}
	}
	
	if (m_FireAction) {
		m_FireOffset.x = std::clamp(m_FireOffset.x + side_flipped * delta_time * 30, -1000.f, 1000.f);
		m_FireOffset.y = std::clamp(m_FireOffset.y + -1 * delta_time * 30, -1000.f, 1000.f);
		m_Sprite.m_Destination.x += m_FireOffset.x;
		m_Sprite.m_Destination.y += m_FireOffset.y;
		if(m_FireOffset.x > 11 || m_FireOffset.x < -11)
		{
			m_FireOffset = { 0.f, 0.f };
			m_FireAction = false;
		}
	}

	m_Projectile.Update(delta_time);
}

void Sword::UpdateAnimation()
{
	m_Projectile.UpdateAnimation();
}

void Sword::Draw(const SDL_RendererFlip& flip)
{
	m_Flip = flip;
	m_Sprite.Draw(m_Flip, m_Rotation, m_Center);
	m_Projectile.Draw();
}

void Sword::Swing()
{
	if (*m_Timer > m_Cooldown) {
		m_Rotation = 0.f;
		m_Action = true;
		*m_Timer = 0.f;
	}
}

void Sword::Fire()
{
	if (*m_Timer > m_Cooldown) {
		m_Projectile.Activate({ float(m_Sprite.m_Destination.x), float(m_Sprite.m_Destination.y) }, m_Facing);
		m_FireAction = true;
		*m_Timer = 0.f;
	}
}
