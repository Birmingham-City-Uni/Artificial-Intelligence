#include "AbilityBar.h"

AbilityBar::AbilityBar()
{

}

void AbilityBar::Initialize(SDL_Rect position, int border, const char* ability_name)
{
	m_Border = border;
	m_Background.Initialize({ 32,32,32,255 }, { 32,32 });
	m_Background.m_Destination = position;
	m_Foreground.Initialize({ 255,255,255,255 }, { 32,32 });
	m_Foreground.m_Destination = { position.x + border, position.y + border, position.w - (2 * border),position.h - (2 * border) };
	m_Name.Initalize("font.ttf", ability_name, 12);
	m_Name.m_Dimensions.x = position.x - m_Name.m_Dimensions.w;
	m_Name.m_Dimensions.y = position.y;
}

void AbilityBar::Draw()
{
	m_Background.Draw();
	m_Foreground.Draw();
	m_Name.Draw();
}

void AbilityBar::ChangeProgress(int ability_percentage)
{
	m_AbilityTimerPercentage = ability_percentage;
	auto initial_width = m_Background.m_Destination.w - (2 * m_Border);
	m_Foreground.m_Destination.w = (initial_width / 100.f) * m_AbilityTimerPercentage;
}

void AbilityBar::ChangeName()
{

}
