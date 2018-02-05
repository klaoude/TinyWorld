#pragma once
#include "Entity.h"

class Player: public Entity
{
public:
	Player();
	~Player();

	void Init(glm::vec2 pos, float speed);
	void Update();
	void Draw(KlaoudeEngine::SpriteBatch& spriteBatch);

private:

};

