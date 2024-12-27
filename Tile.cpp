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

Tile::Tile(Rectangle rect, TileType type, Texture& texture)
	:type(type)
{
	this->x = rect.x;
	this->y = rect.y;
	this->width = rect.width;
	this->height = rect.height;

	this->texture = texture;
}

void Tile::Draw()
{
	DrawTexturePro(texture, { 0,0,(float)texture.width,(float)texture.height },
		{ x, y,(float)texture.width, (float)texture.height },
		{ 0,0 }, 0, WHITE);
}
