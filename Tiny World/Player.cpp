#include "Player.h"

#include <SDL/SDL.h>

Player::Player() : Entity(glm::vec2(50, 50))
{
}

Player::~Player()
{
}

void Player::Init(glm::vec2 pos, float speed)
{
	m_position = pos;
	m_speed = speed;

	m_color = KlaoudeEngine::ColorRGBA8(255, 255, 255, 255);

	KlaoudeEngine::GLTexture texture = KlaoudeEngine::RessourceManager::getTexture("Textures/Player2.png");
	m_texture.init(texture, glm::ivec2(3, 1));
}

void Player::Update(KlaoudeEngine::InputManager& inputManager, float deltaTime)
{
	if (inputManager.isKeyDown(SDLK_LEFT))
	{
		m_position.x -= m_speed * deltaTime;
		m_direction = glm::vec2(1, 0);
	}
	else if (inputManager.isKeyDown(SDLK_RIGHT))
	{
		m_position.x += m_speed * deltaTime;
	}
	if (inputManager.isKeyDown(SDLK_UP))
	{
		m_position.y += m_speed * deltaTime;
	}
	else if (inputManager.isKeyDown(SDLK_DOWN))
	{
		m_position.y -= m_speed * deltaTime;
	}
}

void Player::Draw(KlaoudeEngine::SpriteBatch& spriteBatch)
{
	const glm::vec4 uvRect = m_texture.getUVs(0 );

	glm::vec4 destRect(m_position.x, m_position.y, m_size.x, m_size.y);

	spriteBatch.draw(destRect, uvRect, m_texture.texture.id, 0.0f, m_color, m_direction);
}