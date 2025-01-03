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

#pragma once

#include <iostream>
#include <unordered_map>
#include "raylib.h"

using namespace std;

enum TileType
{
	WALKABLE,
	SOLID,
	TRIGGER_DIALOGUE,
    TRIGGER_DIALOGUE_DESTROYABLE
};

class Tile : public Rectangle
{
private:
	Texture texture;
	Rectangle textureRect;

public:
	TileType type;
    string triggerValue;

	Tile() {}
	Tile(Rectangle rect, TileType type, const char* filename, Rectangle textureRect = { 0,0,0,0 });
	Tile(Rectangle rect, TileType type, Texture& texture, Rectangle textureRect = { 0,0,0,0 });

	void Draw() const;
    bool IsSameTrigger(const Tile& other) const;

    bool operator==(const Tile& other) const;
};