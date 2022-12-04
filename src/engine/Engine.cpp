#include "Engine.h"
#include "Collision.h"
#include "Globals.h"
#include "Input.h"
#include "Pathing.h"

bool Engine::Initialize()
{
	bool globals = globals::Initialize();
	bool renderer = renderer::InitializeRenderer();
	bool texture = texture::Initialize();
	bool sound = sound::InitializeSound();
	bool font = font::InitializeFont();
	bool input = input::InitialzieInput();
	bool pathing = pathing::Initialize();
	font::InitializeDefaultFont();

#ifdef LOGGING
	std::cout << "\n";
	std::cout << "Renderer: " << renderer::GetRenderer() << "\n";
	std::cout << "Default font: " << font::GetDefaultFont().m_Font << "\n\nLoading...\n";
#endif // LOGGING

	m_Music.Initialize("music.wav");
	m_SoundEffect.Initialize("temp.wav");
	m_Tilemap.Initialize("tilemap.png", 16);
	m_Player.Initialize();
	m_Enemy.Initialize();
	m_Text.Initalize("BOB, DESTROYER OF WORLDS");
	m_Text.m_Dimensions.x = 590;
	m_Text.m_Dimensions.y = 10;
	m_HealthBar.Initialize({ 468,30,600,24 }, 4);
	m_AbilityBar.Initialize({ 764,70,300,12 }, 2, "TACTICAL REMOVER");

#ifdef LOGGING
	std::cout << "\n";
#endif // LOGGING

	m_Music.PlayMusic();
	m_SoundEffect.PlaySound();
	m_IsPaused = false;

	return renderer && sound && font && input && globals && texture && pathing; 
}

void Engine::UnInitialize()
{

}

bool Engine::IsRunning()
{
	SDL_PumpEvents();

	SDL_Event event;
	if (SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_QUIT, SDL_QUIT)) {
		return false;
	}

	return true;
}

bool Engine::IsPaused()
{
	return m_IsPaused;
}

void Engine::Resume()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_KEYDOWN) {
			if (input::GetKeyDown(SDL_SCANCODE_ESCAPE)) {
				m_IsPaused = !m_IsPaused;
				input::SetKeyUp(SDL_SCANCODE_ESCAPE, true);
				input::SetKeyDown(SDL_SCANCODE_ESCAPE, false);
				SDL_ShowCursor(m_IsPaused);
#ifdef LOGGING
				std::cout << "Resumed\n";
#endif // LOGGING
			}
		}
	}	
	m_Player.Resume();
}

void Engine::Input()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.scancode < 512) {
				input::SetKeyDown(e.key.keysym.scancode, true);
				input::SetKeyUp(e.key.keysym.scancode, false);
			}
			if (input::GetKeyDown(SDL_SCANCODE_ESCAPE)) {
				m_IsPaused = !m_IsPaused;		
				SDL_ShowCursor(m_IsPaused);
#ifdef LOGGING
				std::cout << "Paused\n";
#endif // LOGGING
			}
#ifdef LOGGING
			if (input::GetKeyDown(SDL_SCANCODE_F1)) {
				m_HealthBar.ChangeHealth(75);
				m_AbilityBar.ChangeProgress(50);
				std::cout << "Key Down: F1!\n";
			}
#endif // LOGGING
		}
		else if (e.type == SDL_KEYUP) {
			if (e.key.keysym.scancode < 512) {
				input::SetKeyDown(e.key.keysym.scancode, false);
				input::SetKeyUp(e.key.keysym.scancode, true);
			}
#ifdef LOGGING
			if (input::GetKeyUp(SDL_SCANCODE_F1)) {
				std::cout << "Key Up: F1!\n";
				input::SetKeyUp(e.key.keysym.scancode, false);
			}
#endif // LOGGING
		}
	}
	m_Player.Input();
#ifdef LOGGING
	pathing::Input();
	m_Enemy.Input();
#endif // LOGGING
	input::SetKeyUp(SDL_SCANCODE_F3, false);
}

void Engine::Update(const float& delta_time)
{
	m_Player.Update(delta_time);
	m_Enemy.Update(delta_time);
}

void Engine::UpdateAnimation(float* num)
{
#ifdef LOGGING
	//std::cout << "AnimStep: " << *num << "\n";
#endif // LOGGING
	*num = 0.0;
	m_Player.UpdateAnimation();
	m_Enemy.UpdateAnimation();
}

void Engine::UpdateAi(float* num)
{
#ifdef LOGGING
	//std::cout << "Update AI!\n";
#endif // LOGGING

	*num = 0.0;
	pathing::Reset();
	for (auto tile : pathing::GetMap()) {
		if (collision::BoxCollision(m_Player.GetCollider(), tile.GetCollider())) {
			pathing::SetObstacle(tile.m_Position.x, tile.m_Position.y, ai::path::Obstacle::Player);
		}
		if (collision::BoxCollision(m_Enemy.GetCollider(), tile.GetCollider())) {
			pathing::SetObstacle(tile.m_Position.x, tile.m_Position.y, ai::path::Obstacle::Ad);
		}
	}
	m_Enemy.UpdateAi(m_Player.GetNodePosition());
	pathing::UpdateAi();
}

void Engine::Draw()
{
	SDL_RenderClear(renderer::GetRenderer());

	m_Tilemap.Draw();
	m_Player.Draw();
	m_Enemy.Draw();
	m_HealthBar.Draw();
	m_Text.Draw();
	m_AbilityBar.Draw();

#ifdef LOGGING
	pathing::Draw();
#endif // LOGGING

	SDL_RenderPresent(renderer::GetRenderer());
}