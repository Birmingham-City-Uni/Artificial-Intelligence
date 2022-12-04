#include "Renderer.h"
#include "Globals.h"

namespace renderer {

	namespace {
		extern SDL_Window* g_Window = nullptr;
		extern SDL_Renderer* g_Renderer = nullptr;
	}
	
	bool InitializeRenderer()
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			std::cout << "SDL could not be initialized! SDL Error: " << SDL_GetError() << "\n";
			return false;
		}
		else
		{
			if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0")) {
				std::cout << "Warning: Linear texture filtering not enabled!" << "\n";
			}
			g_Window = SDL_CreateWindow("Last Dream XIV", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, globals::GetScreenDimensions().w, globals::GetScreenDimensions().h, SDL_WINDOW_SHOWN);
			if (g_Window == NULL) {
				std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
				return false;
			}
			else {
				g_Renderer = SDL_CreateRenderer(g_Window, -1, SDL_RENDERER_ACCELERATED);
				if (g_Renderer == NULL) {
					std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
					return false;
				}
				else {
					SDL_SetRenderDrawColor(g_Renderer, 0x66, 0x66, 0x66, 255);
					SDL_RenderClear(g_Renderer);
					SDL_RenderPresent(g_Renderer);

					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags)) {
						std::cout << "SDL_image could not be initialized! SDL_image error: " << IMG_GetError() << "\n";
						return false;
					}
				}
			}
		}
#ifdef LOGGING
		std::cout << "Renderer Initialized!\n";
#endif // LOGGING
		return true;
	}

	void UninitalizeRenderer()
	{
		IMG_Quit();
		SDL_DestroyRenderer(g_Renderer);
		g_Renderer = nullptr;
		SDL_DestroyWindow(g_Window);
		g_Window = nullptr;
		SDL_Quit();
	}

	SDL_Renderer* GetRenderer()
	{
		return g_Renderer;
	}

	SDL_Window* GetWindow()
	{
		return g_Window;
	}
} // namespace Renderer