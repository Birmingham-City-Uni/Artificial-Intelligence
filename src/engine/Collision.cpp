#include "Collision.h"

namespace  collision{

	const int DistanceSquared(Circle& a, Circle& b) {
		int x = b.m_Position.x - a.m_Position.x;
		int y = b.m_Position.y - a.m_Position.y;
		return x * x + y * y;
	}

	bool BoxCollision(SDL_Rect& lhs, SDL_Rect& rhs) {
		if (
			lhs.x + lhs.w >= rhs.x &&
			rhs.x + rhs.w >= lhs.x &&
			lhs.y + lhs.h >= rhs.y &&
			rhs.y + rhs.h >= lhs.y
			) return true;
		return false;
	}

	bool SpeheCollision(Circle& lhs, Circle& rhs) {
		if (DistanceSquared(lhs, rhs) < (lhs.m_Radius + rhs.m_Radius) * (lhs.m_Radius + rhs.m_Radius))
			return true;
		return false;
	}

	bool ComplexCollision(Circle& lhs, SDL_Rect& rhs) {
		int cX, cY;

		if (lhs.m_Position.x < rhs.x)
			cX = rhs.x;
		else if (lhs.m_Position.x > rhs.x + rhs.w)
			cX = rhs.x + rhs.w;
		else
			cX = lhs.m_Position.x;

		if (lhs.m_Position.y < rhs.y)
			cY = rhs.y;
		else if (lhs.m_Position.y > rhs.y + rhs.h)
			cY = rhs.y + rhs.h;
		else
			cY = lhs.m_Position.y;

		Circle one = { lhs.m_Position.x, lhs.m_Position.y, 0 };
		Circle two = { cX, cY, 0 };

		if (DistanceSquared(one, two) < lhs.m_Radius * lhs.m_Radius)
			return true;
		return false;
	}
}