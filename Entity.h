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

#include "raylib.h"
#include <iostream>

#include "Tile.h"
#include "Animation.h"
#include "Map.h"

using namespace std;

class Entity
{
private:
	vector<Texture2D> textures;

public:
	Vector2 pos, dPos;
	Rectangle hitbox;
	float speed;

	Entity(Vector2 pos, Rectangle hitbox, float speed=100);
    Entity() {}

	virtual void Collision(Map& map);
};

