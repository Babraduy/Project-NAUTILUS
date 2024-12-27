#pragma once

#include "raylib.h"
#include <iostream>

#include "Tile.h"
#include "Animation.h"

using namespace std;

class Entity
{
private:
	vector<Texture2D> textures;

public:
	Vector2 pos, dPos;
	Rectangle hitbox;
	float speed;

	Entity(Vector2 pos, Rectangle hitbox, const char* filename, float speed=100);
	Entity(Vector2 pos, Rectangle hitbox, vector<Texture2D> frames, float speed=100);

	void Collision(vector<Tile> tiles);
};

