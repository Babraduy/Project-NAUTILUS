#include "Tile.h"

Tile::Tile(Rectangle rect, TileType type, const char* filename)
	:type(type)
{
	this->x = rect.x;
	this->y = rect.y;
	this->width = rect.width;
	this->height = rect.height;

	texture = LoadTexture(filename);
}

void Tile::Draw()
{
	DrawTexturePro(texture, { 0,0,(float)texture.width,(float)texture.height },
		{ x, y,(float)texture.width * width/(float)texture.width, (float)texture.height * height / (float)texture.height },
		{ 0,0 }, 0, WHITE);
}
