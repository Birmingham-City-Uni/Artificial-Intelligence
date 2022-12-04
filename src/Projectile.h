#pragma once
#include <functional>
#include <vector>
#include "engine/Globals.h"
#include "engine/Texture.h"
#include "Entity.h"

class Projectile;
class ProjectileManager {
public:
	ProjectileManager() {}

	void Initialize(int no_of_projectiles);
	void Update(const float& delta_time);
	void UpdateAnimation();
	void Draw();

	void Activate(const SDL_FPoint& position, std::shared_ptr<globals::Direction> facing);
	void Deactivate(Projectile& projectile);
public:
	std::vector<Projectile> m_InactiveProjectiles;
	std::vector<Projectile> m_ActiveProjectiles;
	texture::TextureData m_TextureData;
};

class Projectile : public Entity {
public:
	Projectile(texture::TextureData spritesheet, ProjectileManager* manager);

	void Update(const float& delta_time);
	void UpdateAnimation();
	void Draw();
	void Activate(SDL_FPoint position, std::shared_ptr<globals::Direction> facing);
	void Deactivate();
	void SetDirection(int x, int y, int angle);
private:
	bool m_Active;
	int m_Angle;
	texture::TextureData m_Spritesheet;
	SDL_FRect m_Destination;
	ProjectileManager* m_Manager;
};