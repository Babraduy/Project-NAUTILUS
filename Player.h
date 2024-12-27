#pragma once

#include <vector>

#include "Entity.h"

using namespace std;

class Player : public Entity
{
private:
	Animation animManager;

public:
	Rectangle camera;

	void Update(vector<Tile> tiles);

	Player(Vector2 pos, Rectangle hitbox, float speed = 100);
	~Player();
};

