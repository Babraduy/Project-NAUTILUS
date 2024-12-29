#pragma once

#include <iostream>
#include <unordered_map>
#include "raylib.h"

using namespace std;

enum TileType
{
	WALKABLE,
	SOLID,
	TRIGGER
};

class Tile : public Rectangle
{
private:
	Texture texture;
	Rectangle textureRect;

public:
	TileType type;

	Tile() {}
	Tile(Rectangle rect, TileType type, const char* filename, Rectangle textureRect = { 0,0,0,0 });
	Tile(Rectangle rect, TileType type, Texture& texture, Rectangle textureRect = { 0,0,0,0 });

	void Draw();
};