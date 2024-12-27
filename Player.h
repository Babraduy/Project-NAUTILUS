#pragma once

#include <vector>

#include "Entity.h"

using namespace std;

class Player : public Entity
{
private:
	Animation walkAnim;
	vector<Texture2D> front;
	vector<Texture2D> side;
	vector<Texture2D> back;

public:
	Rectangle camera;

	void Update(vector<Tile> tiles);

	Player(Vector2 pos, Rectangle hitbox, vector<Texture2D>& front, vector<Texture2D>& side, vector<Texture2D>& back, float speed = 100);
	~Player();
};

