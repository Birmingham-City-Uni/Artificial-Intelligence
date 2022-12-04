#include "Player.h"
#include <algorithm>
#include "engine/Input.h"

Player::Player() : Entity()
{
	m_Health = 100.f;
	m_MitigationPower = .7f; // 30%
	m_MitigationTimer = 10.f;
	m_MoveSpeed = 128;

	m_GlobalTime = 2;
	m_MitigationTime = 15;
	m_HealPotionTime = 30;
}

void Player::Initialize()
{
	Entity::Initialize();
	m_Image.Texture.Initialize("player.png");
	m_Image.Texture.m_Source = { 0,0,16,32 };
	m_Image.Texture.m_Destination = { 128,128,32,64 };
	m_Image.NoOfAnims = 7;
	m_Collider = { 0,0,28,42 };
	m_Collider.PixelOffset = { 2,16 };
	m_Transform.Position = { 512,128 };

	m_OffGlobal = std::make_shared<float>(2.5f);
	m_Facing = std::make_shared<globals::Direction>(globals::Direction::None);

	m_Sword.Initialize("tilemap.png", m_OffGlobal, m_Facing);

	m_MeleeCooldown.Initialize({ 651,784 }, m_GlobalTime);
	m_RangedCooldown.Initialize({ 713, 784 }, m_GlobalTime);
	m_MitigationCooldown.Initialize({ 775, 784 }, m_MitigationTime);
	m_HealthRegenCooldown.Initialize({ 837, 784 }, m_HealPotionTime);

	m_HealthBar.Initialize({ 618,745,300,24 }, 4);
	m_CharacterName.Initalize("CARLO");
	m_CharacterName.m_Dimensions.x = 727;
	m_CharacterName.m_Dimensions.y = 715;
}

void Player::KeyUp(SDL_Scancode code, const char* message)
{
	if (input::GetKeyUp(code)) {
#ifdef LOGGING
		std::cout << message;
#endif // LOGGING
		input::SetKeyUp(code, false);
	}	
}

void Player::Input()
{
	Entity::Input();
	if (input::GetKeyDown(SDL_SCANCODE_LEFT)) {
		m_Transform.Velocity.x = -m_MoveSpeed;
		m_Image.FlipSprite = SDL_FLIP_HORIZONTAL;
	}
	if (input::GetKeyDown(SDL_SCANCODE_RIGHT)) {
		m_Transform.Velocity.x = m_MoveSpeed;
		m_Image.FlipSprite = SDL_FLIP_NONE;
	}
	if (input::GetKeyDown(SDL_SCANCODE_UP)) {
		m_Transform.Velocity.y = -m_MoveSpeed;
	}	
	if (input::GetKeyDown(SDL_SCANCODE_DOWN)) {
		m_Transform.Velocity.y = m_MoveSpeed;
	}

	if (input::GetKeyDown(SDL_SCANCODE_A)) {
		m_Sword.Swing();
		m_MeleeCooldown.Start();
		m_RangedCooldown.Start();
	}
	if (input::GetKeyDown(SDL_SCANCODE_S)) {
		m_Sword.Fire();
		m_MeleeCooldown.Start();
		m_RangedCooldown.Start();
	}
	if (input::GetKeyDown(SDL_SCANCODE_D)) {
		Mitigation();
		m_MitigationCooldown.Start();
	}
	if (input::GetKeyDown(SDL_SCANCODE_W)) {
		HealthSpell(.03f);
		m_HealthRegenCooldown.Start();
	}
#ifdef LOGGING
	if (input::GetKeyDown(SDL_SCANCODE_Q)) {
		Hit(.03f);
	}
#endif // LOGGING

	if (input::GetKeyUp(SDL_SCANCODE_LEFT)) {
#ifdef LOGGING
		std::cout << "Key Up: Left!\n";
#endif // LOGGING
		m_Transform.Velocity.x = 0;
		input::SetKeyUp(SDL_SCANCODE_LEFT, false);
	}
	if (input::GetKeyUp(SDL_SCANCODE_RIGHT)) {
#ifdef LOGGING
		std::cout << "Key Up: Right!\n";
#endif // LOGGING
		m_Transform.Velocity.x = 0;
		input::SetKeyUp(SDL_SCANCODE_RIGHT, false);
	}
	if (input::GetKeyUp(SDL_SCANCODE_UP)) {
#ifdef LOGGING
		std::cout << "Key Up: Up!\n";
#endif // LOGGING
		m_Transform.Velocity.y = 0;
		input::SetKeyUp(SDL_SCANCODE_UP, false);
	}
	if (input::GetKeyUp(SDL_SCANCODE_DOWN)) {
#ifdef LOGGING
		std::cout << "Key Up: Down!\n";
#endif // LOGGING
		m_Transform.Velocity.y = 0;
		input::SetKeyUp(SDL_SCANCODE_DOWN, false);
	}
	KeyUp(SDL_SCANCODE_A, "Sword swing!\n");
	KeyUp(SDL_SCANCODE_S, "Ranged attack!\n");
	KeyUp(SDL_SCANCODE_D, "Mitigation!\n");
	KeyUp(SDL_SCANCODE_W, "Health potion!\n");
#ifdef LOGGING
	KeyUp(SDL_SCANCODE_Q, "Debug Self-Damage!\n");
#endif // LOGGING
}

void Player::Update(const float delta_time)
{
	if (m_Transform.Velocity.y < 0) *m_Facing = globals::Direction::North;
	if (m_Transform.Velocity.x > 0) *m_Facing = globals::Direction::East;
	if (m_Transform.Velocity.y < 0 && m_Transform.Velocity.x > 0) *m_Facing = globals::Direction::NorthEast;
	if (m_Transform.Velocity.y > 0) *m_Facing = globals::Direction::South;
	if (m_Transform.Velocity.y > 0 && m_Transform.Velocity.x > 0) *m_Facing = globals::Direction::SouthEast;
	if (m_Transform.Velocity.x < 0) *m_Facing = globals::Direction::West;
	if (m_Transform.Velocity.y > 0 && m_Transform.Velocity.x < 0) *m_Facing = globals::Direction::SouthWest;
	if (m_Transform.Velocity.y < 0 && m_Transform.Velocity.x < 0) *m_Facing = globals::Direction::NorthWest;
	if (m_Transform.Velocity.x == 0 && m_Transform.Velocity.y == 0) *m_Facing = globals::Direction::None;

	auto screen_dimensions = globals::GetScreenDimensions();
	m_Transform.Position.x = std::clamp(m_Transform.Position.x + static_cast<float>(m_Transform.Velocity.x) * delta_time, 0.f, screen_dimensions.w - 32.f); // Offsetting image size
	m_Transform.Position.y = std::clamp(m_Transform.Position.y + static_cast<float>(m_Transform.Velocity.y) * delta_time, -16.f, screen_dimensions.h - 64.f); // Offsetting image size
	m_Collider.Dimensions.x = m_Transform.Position.x + m_Collider.PixelOffset.x;
	m_Collider.Dimensions.y = m_Transform.Position.y + m_Collider.PixelOffset.y;
	m_Image.Texture.m_Destination.x = m_Transform.Position.x;
	m_Image.Texture.m_Destination.y = m_Transform.Position.y;

	SDL_FPoint sword_position = { m_Transform.Position.x + ((!m_Image.FlipSprite << 5) - 14) , m_Transform.Position.y + 2 }; // Sets the sword left or right of the player
	m_Sword.Update(delta_time, sword_position);

	*m_OffGlobal += delta_time;
	m_MeleeCooldown.Update(delta_time);
	m_RangedCooldown.Update(delta_time);
	m_HealthRegenCooldown.Update(delta_time);
	m_MitigationCooldown.Update(delta_time);
	m_MitigationTimer += delta_time;
}

void Player::Resume()
{
	input::SetKeyDown(SDL_SCANCODE_LEFT, false);
	input::SetKeyDown(SDL_SCANCODE_RIGHT, false);
	input::SetKeyDown(SDL_SCANCODE_UP, false);
	input::SetKeyDown(SDL_SCANCODE_DOWN, false);
	input::SetKeyDown(SDL_SCANCODE_A, false);
	input::SetKeyDown(SDL_SCANCODE_S, false);
	input::SetKeyDown(SDL_SCANCODE_W, false);
	input::SetKeyDown(SDL_SCANCODE_D, false);
	m_Transform.Velocity = {0,0};
}

void Player::UpdateAnimation()
{
	Entity::UpdateAnimation();
	m_Sword.UpdateAnimation();
}

void Player::Draw()
{
	Entity::Draw();
	m_Image.Texture.Draw(m_Image.FlipSprite);
	m_Sword.Draw(m_Image.FlipSprite);
	m_MeleeCooldown.Draw();
	m_RangedCooldown.Draw();
	m_HealthRegenCooldown.Draw();
	m_MitigationCooldown.Draw();
	m_HealthBar.Draw();
	m_CharacterName.Draw();
}

void Player::HealthSpell(float heal_amount)
{
	m_Health = std::clamp(m_Health + heal_amount, 0.f, 100.f);
	m_HealthBar.ChangeHealth(m_Health);
}

void Player::Mitigation()
{
	m_MitigationTimer = 0.f;
}

void Player::Hit(float damage_amount)
{
	if (m_MitigationTimer < m_MitigationTime) {
		m_Health = std::clamp(m_Health - (damage_amount * m_MitigationPower), 0.f, 100.f);
	}else{
		m_Health = std::clamp(m_Health - damage_amount, 0.f, 100.f);
	}
	m_HealthBar.ChangeHealth(m_Health);
	if (m_Health <= 0.f) {
		std::cout << "You have DIED!\n";
	}
}