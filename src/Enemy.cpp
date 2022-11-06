#include "Enemy.h"
#include <algorithm>
#include <cmath>
#include "engine/Globals.h"
#include "engine/Pathing.h"

Enemy::Enemy() : Entity()
{
	m_Collider.Dimensions = { 6,4,50,56 };
	m_Collider.PixelOffset = { 6,4 };
	m_Transform.Position = { 736,256 };
	m_Transform.Velocity = { 32.f,32.f };
	m_Transform.RotationSpeed = .5f;
	m_Image.NoOfAnims = 7;
	m_StoppingDistance = 10.f;
	m_GoalTile = { 0,0 };
	m_SmoothedPath = ai::path::CreatePath();

	m_FiniteStateMachine = ai::fsm::GetStateManager();
	m_Ammo = 3;
	m_Timer = 1.f;
	
	m_IdleState = ai::fsm::CreateState(m_FiniteStateMachine, [&](const float delta_time) {
		if (m_Timer >= 2.f) {
			m_Timer = 0.f;
#ifdef LOGGING
			std::cout << "Idle state\nSwitching to attack state\n";
#endif // LOGGING
			m_FiniteStateMachine->SetState(m_AttackState);
		}
	});

	m_AttackState = ai::fsm::CreateState(m_FiniteStateMachine, [&](const float delta_time) {
		if (m_Timer >= 1.f) {
			m_Timer = 0;
#ifdef LOGGING
			std::cout << "Shoot state - shooting\n";
#endif // LOGGING
			if (m_Ammo <= 0) {
#ifdef LOGGING
				std::cout << "Shoot state - out of ammo\nSwitch to idle state\n";
#endif // LOGGING
				m_Ammo = 3;
				m_GoalTile = { 0.f, 0.f };
				m_FiniteStateMachine->SetState(m_DieState);
			}
			else {
#ifdef LOGGING
				std::cout << "Shoot state - shoot\t " << m_Ammo-1 << " shots remaining" << "\n";
#endif // LOGGING
				m_Ammo--;
				GoalTile();
			}
		}
	});

	m_WanderState = ai::fsm::CreateState(m_FiniteStateMachine, [&](const float delta_time) {
		if (m_Timer >= 5.f) {
			m_Timer = 0;
#ifdef LOGGING
			std::cout << "Spawn wander finished\nSwitching to 'n' state\n";
#endif // LOGGING
		}
	});

	m_DieState = ai::fsm::CreateState(m_FiniteStateMachine, [&](const float delta_time) {
		if (m_Timer >= 1.f) {
			m_Timer = 0;
#ifdef LOGGING
			std::cout << "Die state finished\nSwitching to finished state\n";
#endif // LOGGING
			m_FiniteStateMachine->KillManager();
		}
	});

	m_SpawnState = ai::fsm::CreateState(m_FiniteStateMachine, [&](const float delta_time) {
		if (m_Timer >= 2.f) {
			m_Timer = 0;
#ifdef LOGGING
			std::cout << "Spawn state finished\nSwitching to idle state\n";
#endif // LOGGING
			m_FiniteStateMachine->SetState(m_IdleState);
		}
	});

	m_FiniteStateMachine->SetState(m_IdleState);
}

void Enemy::Initialize()
{
	Entity::Initialize();
	m_Image.Texture.Initialize("ad.png");
	m_Image.Texture.m_Source = { 0,0,32,32 };
	m_Image.Texture.m_Destination = { 128,128,64,64 };
}
#ifdef LOGGING
void Enemy::Input()
{
	Entity::Input();
}
#endif // LOGGING

void Enemy::Update(const float delta_time)
{
	auto screen_dimensions = globals::GetScreenDimensions();
	Move(delta_time);
	//FollowSmoothedPath(delta_time);

	m_Transform.Position.x = std::clamp(m_Transform.Position.x, 0.f, screen_dimensions.w - 32.f); // Offsetting image size
	m_Transform.Position.y = std::clamp(m_Transform.Position.y, -16.f, screen_dimensions.h - 64.f); // Offsetting image size
	m_Collider.Dimensions.x = m_Transform.Position.x + m_Collider.PixelOffset.x;
	m_Collider.Dimensions.y = m_Transform.Position.y + m_Collider.PixelOffset.y;
	m_Image.Texture.m_Destination.x = m_Transform.Position.x;
	m_Image.Texture.m_Destination.y = m_Transform.Position.y;

	m_Timer += delta_time;
	m_FiniteStateMachine->Update(delta_time);
}

void Enemy::UpdateAnimation()
{
	Entity::UpdateAnimation();
}

void Enemy::UpdateAi(Vector2 goal)
{
	// TODO @RyanWestwood : Neaten entire project to use Vector2 over SDL_Point where needed.
	//						clean this code!
	Vector2 start_pos = { (int)m_Transform.Position.x / 32 + 1, (int)m_Transform.Position.y / 32 + 1 };
	Vector2 new_goal = { (int)goal.x, (int)goal.y };
	m_Path = pathing::CreatePath(start_pos, new_goal, pathing::Algo::A_Star);
	m_SmoothedPath->UpdatePath(m_Path, start_pos, 5.f, m_StoppingDistance); // TODO: fix this.
}

void Enemy::Draw()
{
	Entity::Draw();
	m_Image.Texture.Draw();
}

void Enemy::GoalTile()
{
	if(m_Path.size() <= 1) return;
	auto current_position = { (int)m_Transform.Position.x / 32 + 1, (int)m_Transform.Position.y / 32 + 1 };
	m_GoalTile = SDL_FPoint{ (float)m_Path[1].x, (float)m_Path[1].y };
}

void Enemy::Move(const float delta_time)
{
	if (m_GoalTile.x == 0.f && m_GoalTile.y == 0.f) return;

	SDL_FPoint GreenBox = { (int)m_Transform.Position.x / 32 + 1, (int)m_Transform.Position.y / 32 + 1 };
	SDL_FPoint Difference = { m_GoalTile.x - GreenBox.x, m_GoalTile.y - GreenBox.y };
	m_Transform.Position.x += Difference.x;
	m_Transform.Position.y += Difference.y;
}

void Enemy::FollowSmoothedPath(const float delta_time)
{
	if (m_SmoothedPath->m_LookPoints.empty()) return;
	int finish_line_index = m_SmoothedPath->m_FinishLineIndex;
	int path_index = 0;

	bool following_path = true;
	float speed_percentage = 1.f;

	Vector2 position_2d = { (int)m_Transform.Position.x /32, (int)m_Transform.Position.y/32 };
	while (m_SmoothedPath->m_TurnBoundaries[path_index].HasCrossedLine(position_2d)) {
		if (path_index == finish_line_index) {
			following_path = false;
			break;
		}
		else {
			path_index++;
		}
	}

	if (following_path) {
		if(path_index >= m_SmoothedPath->m_SlowDownIndex && m_StoppingDistance > 0){
			ai::path::Line& line = m_SmoothedPath->m_TurnBoundaries.at(finish_line_index);
			float distance_from_point = line.DistanceFromPoint(position_2d) / m_StoppingDistance;
			if(!std::isnan(distance_from_point)){
				speed_percentage = std::clamp(distance_from_point, 0.f, 1.f);
			}
			if (speed_percentage < 0.01f) {
				following_path = false;
			}
		}

		Vector2 dir = { m_SmoothedPath->m_LookPoints[path_index] - m_Transform.Position };
		const float angle_degrees = std::atan2f(dir.y, dir.x) * (180.0 / 3.141592653589793238463);
		m_Transform.Rotation = std::lerp(m_Transform.Rotation, angle_degrees, m_Transform.RotationSpeed * delta_time);
		m_Transform.Position.x += std::cos(angle_degrees) * m_Transform.Velocity.x * speed_percentage * delta_time;
		m_Transform.Position.y += std::sin(angle_degrees) * m_Transform.Velocity.y * speed_percentage * delta_time;
	}
}