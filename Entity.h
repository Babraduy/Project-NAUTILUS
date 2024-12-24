#pragma once

#include "raylib.h"
#include <iostream>

#include "Tile.h"

using namespace std;

class Entity
{
private:
	Texture2D texture;

public:
	Vector2 pos, dPos, scale;
	Rectangle hitbox;
	float speed;

	Entity(Vector2 pos, Rectangle hitbox, const char* filename, Vector2 scale = {1,1}, float speed=100);
	~Entity();

	void Draw();

	void Collision(vector<Tile> tiles);
};

