#pragma once
#include "SDL.h"

namespace collision {

	struct Circle {
		SDL_Point m_Position;
		int m_Radius;
	};

	bool BoxCollision(SDL_Rect& lhs, SDL_Rect& rhs);
	bool SpeheCollision(Circle& lhs, Circle& rhs);
	bool ComplexCollision(Circle& lhs, SDL_Rect& rhs);
}