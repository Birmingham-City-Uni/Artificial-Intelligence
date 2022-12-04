#include "Projectile.h"
#include <algorithm>
#include "engine/Globals.h"
#include "engine/Renderer.h"

Projectile::Projectile(texture::TextureData spritesheet, ProjectileManager* manager)
{
	m_Active = false;
	m_Manager = manager;
	m_Spritesheet = spritesheet;
	m_Spritesheet.m_Source.w = 32;
	m_Spritesheet.m_Source.h = 32;
	m_Destination = { 0,0,32,32 };
	m_Image.NoOfAnims = 7;
}

void Projectile::Activate(SDL_FPoint position, std::shared_ptr<globals::Direction> facing) {
	m_Active = true;
	m_Transform.Position = { position.x, position.y };
	m_Transform.Velocity = { 512, 0 };
	m_Destination = { m_Transform.Position.x, m_Transform.Position.y,32,32 };

	if (*facing == globals::Direction::North) SetDirection(0,-512, 270);
	if (*facing == globals::Direction::NorthEast) SetDirection(512,-512, 315);
	if (*facing == globals::Direction::East) SetDirection(512, 0, 0);
	if (*facing == globals::Direction::SouthEast) SetDirection(512, 512, 45);
	if (*facing == globals::Direction::South) SetDirection(0, 512, 90);
	if (*facing == globals::Direction::SouthWest) SetDirection(-512, 512, 135);
	if (*facing == globals::Direction::West) SetDirection(-512, 0, 180);
	if (*facing == globals::Direction::NorthWest) SetDirection(-512, -512, 225);
}

void Projectile::Deactivate()
{
	m_Active = false;
	m_Manager->Deactivate(*this);
}

void Projectile::SetDirection(int x, int y, int angle){
	m_Transform.Velocity = { (float)x, (float)y };
	m_Angle = angle;
}

void Projectile::Update(const float& delta_time)
{
	auto screen_size = globals::GetScreenDimensions();
	if (!m_Active) return;
	if (m_Transform.Position.x < -14 || m_Transform.Position.x >= screen_size.w + 14) Deactivate();
	if (m_Transform.Position.y < -14 || m_Transform.Position.y >= screen_size.h + 14) Deactivate();

	m_Transform.Position.x += m_Transform.Velocity.x * delta_time;
	m_Transform.Position.y += m_Transform.Velocity.y * delta_time;
	m_Destination.x = m_Transform.Position.x;
	m_Destination.y = m_Transform.Position.y;
}

void Projectile::UpdateAnimation()
{
	if (!m_Active) return;
	Entity::UpdateAnimation();
}

void Projectile::Draw()
{
	if (!m_Active) return;
	SDL_RenderCopyExF(renderer::GetRenderer(), m_Spritesheet.m_Texture, &m_Spritesheet.m_Source, &m_Destination, m_Angle, 0, SDL_FLIP_NONE);
}

void ProjectileManager::Initialize(int no_of_projectiles)
{
	auto texture = texture::LoadTexture("projectile.png");
	m_TextureData.m_Texture = texture.m_Texture;
	m_TextureData.m_Source = texture.m_Source;
	m_InactiveProjectiles = { Uint64(no_of_projectiles), Projectile(m_TextureData, this) };
	m_ActiveProjectiles.reserve(no_of_projectiles);
}

void ProjectileManager::Update(const float& delta_time)
{
	for (Projectile& projectile : m_ActiveProjectiles) {
		projectile.Update(delta_time);
	}
}

void ProjectileManager::UpdateAnimation()
{
	for(Projectile& projectile : m_ActiveProjectiles){
		projectile.UpdateAnimation();
	}
}

void ProjectileManager::Draw()
{
	for (Projectile& projectile : m_ActiveProjectiles) {
		projectile.Draw();
	}
}

void ProjectileManager::Activate(const SDL_FPoint& position, std::shared_ptr<globals::Direction> facing)
{
	m_InactiveProjectiles.front().Activate(position, facing);
	m_ActiveProjectiles.insert(m_ActiveProjectiles.end(), std::make_move_iterator(m_InactiveProjectiles.begin()),
		std::make_move_iterator(m_InactiveProjectiles.begin()+1));
	m_InactiveProjectiles.erase(begin(m_InactiveProjectiles), begin(m_InactiveProjectiles) + 1);
}

void ProjectileManager::Deactivate(Projectile& projectile)
{
	m_InactiveProjectiles.insert(m_InactiveProjectiles.end(), std::make_move_iterator(m_ActiveProjectiles.begin()),
		std::make_move_iterator(m_ActiveProjectiles.begin() + 1));
	m_ActiveProjectiles.erase(begin(m_ActiveProjectiles), begin(m_ActiveProjectiles) + 1);
}