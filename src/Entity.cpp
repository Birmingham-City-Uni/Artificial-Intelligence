#include "Entity.h"
#include "engine/Renderer.h"
#include "engine/Input.h"

Entity::Entity() {
	m_Collider.Dimensions = { 0,0,0,0 };
	m_Collider.PixelOffset = {0, 0};
	m_Transform.Position = { 0,0 };
	m_Transform.Rotation = 0.f;
	m_Transform.RotationSpeed = 0.f;
	m_Transform.Velocity = { 0, 0 };
	m_Transform.Direction = 0;
	m_Image.Texture = Sprite();
	m_Image.NoOfAnims = 1;
	m_Image.AnimStep = 0;
	m_Image.FlipSprite = SDL_FLIP_NONE;
}

void Entity::Initialize()
{
#if LOGGING
	m_DebugCollider = texture::LoadSolidColourTexture({ 0,255,255,128 }, { 32,32 });
#endif // LOGGING
}

void Entity::Input()
{
#if LOGGING
	if (input::GetKeyUp(SDL_SCANCODE_F3)) {
		m_DebugActivate = !m_DebugActivate;
	}
#endif // LOGGING
}

void Entity::UpdateAnimation()
{
	m_Image.AnimStep >= m_Image.NoOfAnims ? m_Image.AnimStep = 0 : m_Image.AnimStep++;
	m_Image.Texture.m_Source.x = m_Image.Texture.m_Source.w * m_Image.AnimStep;
}

void Entity::Draw()
{
#if LOGGING
	if (m_DebugActivate){
		SDL_RenderCopy(renderer::GetRenderer(), m_DebugCollider.m_Texture, &m_DebugCollider.m_Source, &m_Collider.Dimensions);
	}
#endif // LOGGING
}

SDL_Rect& Entity::GetCollider()
{
	return m_Collider.Dimensions;
}

Vector2 Entity::GetNodePosition()
{
	return { m_Transform.Position.x / 32, m_Transform.Position.y / 32 };
}