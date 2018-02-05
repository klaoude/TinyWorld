#include "Entity.h"

Entity::Entity(glm::vec2 size)
{
	m_size = size;
}

Entity::~Entity()
{
}

void Entity::Update(float deltaTime)
{

}

void Entity::Draw(KlaoudeEngine::SpriteBatch& spriteBatch)
{
	const glm::vec4 uvRect(0.f, 0.f, 0.1f, 0.5f);

	glm::vec4 destRect(m_position.x, m_position.y, m_size.x, m_size.y);

	spriteBatch.draw(destRect, uvRect, m_texture.texture.id, 0.0f, m_color, m_direction);
}