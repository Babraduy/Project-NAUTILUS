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

public:
	TileType type;

	Tile() {}
	Tile(Rectangle rect, TileType type, const char* filename);
	Tile(Rectangle rect, TileType type, Texture& texture);

	void Draw();
};