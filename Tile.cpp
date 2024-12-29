#include "Tile.h"

Tile::Tile(Rectangle rect, TileType type, const char* filename, Rectangle textureRect)
	:type(type), textureRect(textureRect)
{
	this->x = rect.x;
	this->y = rect.y;
	this->width = rect.width;
	this->height = rect.height;

	texture = LoadTexture(filename);

	if (textureRect.width == 0 && textureRect.height == 0)
	{
		this->textureRect = { textureRect.x, textureRect.y, (float)texture.width, (float)texture.height };
	}
}

Tile::Tile(Rectangle rect, TileType type, Texture& texture, Rectangle textureRect)
	:type(type), textureRect(textureRect)
{
	this->x = rect.x;
	this->y = rect.y;
	this->width = rect.width;
	this->height = rect.height;

	this->texture = texture;

	if (textureRect.width == 0 && textureRect.height == 0)
	{
		this->textureRect = { textureRect.x, textureRect.y, (float)texture.width, (float)texture.height };
	}
}

void Tile::Draw()
{
	DrawTexturePro(texture, textureRect,
		{ x, y,textureRect.width, textureRect.height},
		{ 0,0 }, 0, WHITE);
}
