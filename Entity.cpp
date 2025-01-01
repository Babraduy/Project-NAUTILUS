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

#include "Entity.h"

Entity::Entity(Vector2 pos, Rectangle hitbox, float speed)
	: pos(pos), hitbox(hitbox), speed(speed), dPos({ 0,0 })
{
	this->hitbox.x += pos.x;
	this->hitbox.y += pos.y;
}

void Entity::Collision(Map& map)
{
	vector<Tile> tiles = map.GetNearbyTiles({ pos.x - map.tileSize, pos.y - map.tileSize, map.tileSize * 3, map.tileSize * 3 });

	pos.x += dPos.x;
	hitbox.x += dPos.x;

	for (const Tile& tile : tiles)
	{
		if (CheckCollisionRecs(hitbox, tile))
		{
			if (tile.type == SOLID)
			{
				if (dPos.x > 0)
				{
					pos.x -= hitbox.x + hitbox.width - tile.x;
					hitbox.x -= hitbox.x + hitbox.width - tile.x;
				}
				else if (dPos.x < 0)
				{
					pos.x -= hitbox.x - (tile.x + tile.width);
					hitbox.x -= hitbox.x - (tile.x + tile.width);
				}
			}
		}
	}

	pos.y += dPos.y;
	hitbox.y += dPos.y;

	for (const Tile& tile : tiles)
	{
		if (CheckCollisionRecs(hitbox, tile))
		{
			if (tile.type == SOLID)
			{
				if (dPos.y > 0)
				{
					pos.y -= hitbox.y + hitbox.height - tile.y;
					hitbox.y -= hitbox.y + hitbox.height - tile.y;
				}
				else if (dPos.y < 0)
				{
					pos.y -= hitbox.y - (tile.y + tile.height);
					hitbox.y -= hitbox.y - (tile.y + tile.height);
				}
			}
		}
	}
}
