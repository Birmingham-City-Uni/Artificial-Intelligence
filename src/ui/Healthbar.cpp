#include "Healthbar.h"

HealthBar::HealthBar()
{

}

void HealthBar::Initialize(SDL_Rect position, int border)
{
	m_Border = border;
	m_Background.Initialize({ 32,32,32,255 }, { 32,32 });
	m_Background.m_Destination = position;	
	m_Foreground.Initialize({ 255,0,0,255 }, { 32,32 });
	m_Foreground.m_Destination = { position.x + border, position.y + border, position.w - (2 * border),position.h - (2 * border) };
}

void HealthBar::Draw()
{
	m_Background.Draw();
	m_Foreground.Draw();
}

void HealthBar::ChangeHealth(int health_percentage)
{
	m_Health = health_percentage;
	auto initial_width = m_Background.m_Destination.w - (2 * m_Border);
	m_Foreground.m_Destination.w = (initial_width / 100.f) * m_Health;
}