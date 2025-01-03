/*  Project NAUTILUS
	Copyright (C) 2024  Babraduy

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

#include "Player.h"

void Player::Update(Map& map)
{
	dPos = { 0,0 };

	if (dialogueManager.isClosed)
	{
		if (IsKeyDown(KEY_W))
		{
			dPos.y -= speed * GetFrameTime();

			animManager.SetAnimation("player_walk");
		}
		if (IsKeyDown(KEY_A))
		{
			dPos.x -= speed * GetFrameTime();

			animManager.SetAnimation("player_walk");
			animManager.flipX = -1;
		}
		if (IsKeyDown(KEY_S))
		{
			dPos.y += speed * GetFrameTime();

			animManager.SetAnimation("player_walk");
		}
		if (IsKeyDown(KEY_D))
		{
			dPos.x += speed * GetFrameTime();

			animManager.SetAnimation("player_walk");
			animManager.flipX = 1;
		}
	}

	if (dPos.x == 0 && dPos.y == 0)
	{
		animManager.SetAnimation("amilia");
	}


	Collision(map);

	animManager.Update(pos);
}

void Player::Collision(Map& map)
{
	Entity::Collision(map);

	vector<Tile> tiles = map.GetNearbyTiles({ pos.x, pos.y, map.tileSize, map.tileSize });

	/* Check for triggers */
	for (const Tile& tile : tiles)
	{
		if (CheckCollisionRecs(hitbox, tile))
		{
			switch (tile.type)
			{
			case TRIGGER_DIALOGUE_DESTROYABLE:
				dialogueManager.LoadText(tile.triggerValue);
				for (const Tile& tile2 : map.GetNearbyTiles({ 0,0,map.size.x * map.tileSize,map.size.y * map.tileSize }))
				{
					if (tile.IsSameTrigger(tile2))
					{
						map.RemoveTile(tile2);
					}
				}
				break;
			}
		}
	}
}

Player::Player(Vector2 pos, Rectangle hitbox, float speed)
	:Entity(pos, hitbox, speed)
{
	animManager = Animation("amilia");
	dialogueManager = Dialogue("test1", GetFontDefault(), 50);

	if (hitbox.width == 0)
	{
		this->hitbox.width = animManager.frames[0].w;
	}
	if (hitbox.height == 0)
	{
		this->hitbox.height = animManager.frames[0].h;
	}
}

Player::~Player() { }
