#pragma once

#include <KlaoudeEngine\SpriteBatch.h>
#include <KlaoudeEngine\TileSheet.h>
#include <KlaoudeEngine\RessourceManager.h>

class Entity
{
public:
	Entity(glm::vec2 size);	
	virtual ~Entity();

	virtual void Update(float deltaTime);

	void Draw(KlaoudeEngine::SpriteBatch& spriteBatch);

	glm::vec2 getPos() const { return m_position; }

protected:
	glm::vec2 m_position, m_size, m_direction;
	KlaoudeEngine::ColorRGBA8 m_color;
	KlaoudeEngine::TileSheet m_texture;
	float m_speed;
};

