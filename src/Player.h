#pragma once
#include "engine/Globals.h"
#include "engine/Font.h"
#include "ui/Cooldown.h"
#include "ui/Healthbar.h"
#include "Entity.h"
#include "Staff.h"
#include "Sword.h"

class Player : public Entity {
public: 
	Player();

	void Initialize();
	void KeyUp(SDL_Scancode code, const char* message);

	void Input() override;
	void Update(const float delta_time) override;
	void Resume();
	void UpdateAnimation() override;
	void Draw() override;

	void HealthSpell(float heal_amount);
	void Mitigation();
	void Hit(float damage_amount);

public:
	Sword m_Sword;
	std::shared_ptr<float> m_OffGlobal;
	std::shared_ptr<float> m_Global;
	std::shared_ptr<globals::Direction> m_Facing;
	
	Cooldown m_MeleeCooldown;
	Cooldown m_RangedCooldown;
	Cooldown m_HealthRegenCooldown;
	Cooldown m_MitigationCooldown;
	HealthBar m_HealthBar;
	Text m_CharacterName;

	float m_Health;
	float m_MitigationPower;
	float m_MitigationTimer;

	int m_MoveSpeed;
	int m_GlobalTime;
	int m_HealPotionTime;
	int m_MitigationTime;
};