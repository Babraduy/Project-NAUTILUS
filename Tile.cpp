/*  Project NAUTILUS
	Copyright (C) 2024-2025  Babraduy

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>. */

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

void Tile::Draw() const
{
	DrawTexturePro(texture, textureRect,
		{ x, y,textureRect.width, textureRect.height},
		{ 0,0 }, 0, WHITE);
}

bool Tile::IsSameTrigger(const Tile& other) const
{
	return type == other.type && triggerValue == other.triggerValue;
}

bool Tile::operator==(const Tile& other) const
{
	return x == other.x && y == other.y && type == other.type && triggerValue == other.triggerValue;
}
