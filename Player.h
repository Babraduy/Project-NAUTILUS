#pragma once

#include <vector>

#include "Entity.h"

using namespace std;

class Player : public Entity
{
private:

public:
	Rectangle camera;

	void Update(vector<Tile> tiles);

	Player(Vector2 pos, Rectangle hitbox, const char* filename, Vector2 scale = { 1,1 }, float speed = 1);
	~Player();
};

