#pragma once

#include "Entity.h"

class Player : public Entity
{
private:

public:
	void Update();

	Player(Vector2 pos, Rectangle hitbox, const char* filename, Vector2 scale = { 1,1 }, float speed = 1);
	~Player();
};

