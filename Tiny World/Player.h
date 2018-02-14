#pragma once
#include "Entity.h"

#include <KlaoudeEngine/InputManager.h>

class Player: public Entity
{
public:
	Player();
	~Player();

	void Init(glm::vec2 pos, float speed);
	void Update(KlaoudeEngine::InputManager& inputManager, float deltaTime);
	void Draw(KlaoudeEngine::SpriteBatch& spriteBatch);

private:

};

