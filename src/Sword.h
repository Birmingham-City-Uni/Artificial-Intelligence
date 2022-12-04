#pragma once
#include <vector>
#include "engine/Globals.h"
#include "Attack.h"
#include "Projectile.h"

class Sword : public Attack{
public:
	Sword();

	void Initialize(const char* filename, std::shared_ptr<float> timer, std::shared_ptr<globals::Direction> facing);
	void Update(const float& delta_time, const SDL_FPoint position);
	void UpdateAnimation();
	void Draw(const SDL_RendererFlip& flip = SDL_FLIP_NONE);
	void Swing();
	void Fire();

private:
	bool m_FireAction;
	SDL_FPoint m_FireOffset;
	ProjectileManager m_Projectile;
	std::shared_ptr<globals::Direction> m_Facing;
};