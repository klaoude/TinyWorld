#include "Player.h"

Player::Player() : Entity(glm::vec2(16, 16))
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

	KlaoudeEngine::GLTexture texture = KlaoudeEngine::RessourceManager::getTexture("Textures/Player.png");
	m_texture.init(texture, glm::ivec2(6, 3));
}

void Player::Update()
{

}

void Player::Draw(KlaoudeEngine::SpriteBatch& spriteBatch)
{
	const glm::vec4 uvRect(0.f, 0.f, 0.1f, 0.5f);

	glm::vec4 destRect(m_position.x, m_position.y, m_size.x, m_size.y);

	spriteBatch.draw(destRect, uvRect, m_texture.texture.id, 0.0f, m_color, m_direction);
}