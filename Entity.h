#pragma once

#include "raylib.h"
#include <iostream>
using namespace std;

class Entity
{
private:

public:
	Vector2 pos, scale;
	Rectangle hitbox;
	Image img;
	Texture2D texture;
	float speed;

	Entity(Vector2 pos, Rectangle hitbox, const char* filename, Vector2 scale = {1,1}, float speed=1);
	~Entity();

	void Draw();

	void Collision();
};

