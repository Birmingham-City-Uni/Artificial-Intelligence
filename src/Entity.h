#pragma once
#include <SDL.h>
#include <math/Vector2.h>
#include "engine/Texture.h"

struct Collider {
	SDL_Rect Dimensions;
	Vector2 PixelOffset;
};

struct Transform {
	Vector2 Position;
	Vector2 Velocity;
	float Rotation;
	float RotationSpeed;
	char Direction;
};

struct Image {
	Sprite Texture;
	char AnimStep;
	char NoOfAnims;
	SDL_RendererFlip FlipSprite;
};

class Entity {
public:
	Entity();

	virtual void Initialize();
	virtual void Input();
	virtual void Update(const float delta_time) {}
	virtual void UpdateAnimation();
	virtual void Draw();

	SDL_Rect& GetCollider();
	Vector2 GetNodePosition();

public:
	Collider m_Collider;
	Transform m_Transform;
	Image m_Image;
#if LOGGING
	texture::TextureData m_DebugCollider;
	bool m_DebugActivate = false;
#endif // LOGGING
};