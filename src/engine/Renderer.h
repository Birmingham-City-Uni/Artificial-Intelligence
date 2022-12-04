#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

namespace renderer {

	bool InitializeRenderer();
	void UninitalizeRenderer();

	SDL_Renderer* GetRenderer();
	SDL_Window* GetWindow();
} // namespace Renderer