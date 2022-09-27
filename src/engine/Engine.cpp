#include "Engine.h"
#include "Texture.h"

bool Engine::Initialize()
{
	bool renderer = Renderer::InitalizeRenderer();
	bool sound = Sound::InitalizeSound();

	return renderer && sound; 
}

void Engine::Unintialize()
{
	Sound::UninitalizeSound();
	Renderer::UninitalizeRenderer();
}

bool Engine::IsRunning()
{
	return true;
}

bool Engine::IsPaused()
{
	return false;
}

void Engine::Resume()
{

}

void Engine::Input()
{

}

void Engine::Update(double delta_time)
{

}

void Engine::Draw()
{
	SDL_RenderClear(Renderer::GetRenderer());

	SDL_RenderPresent(Renderer::GetRenderer());
}