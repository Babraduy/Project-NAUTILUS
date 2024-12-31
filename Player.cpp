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

void Player::Update(vector<Tile> tiles)
{
	dPos = { 0,0 };

	if (IsKeyDown(KEY_W))
	{
		dPos.y-= speed * GetFrameTime();

		animManager.SetAnimation("player_walk");
	}
	if (IsKeyDown(KEY_A))
	{
		dPos.x-= speed * GetFrameTime();

		animManager.SetAnimation("player_walk");
		animManager.flipX = -1;
	}
	if (IsKeyDown(KEY_S))
	{
		dPos.y+=speed * GetFrameTime();

		animManager.SetAnimation("player_walk");
	}
	if (IsKeyDown(KEY_D))
	{
		dPos.x+=speed * GetFrameTime();

		animManager.SetAnimation("player_walk");
		animManager.flipX = 1;
	}

	if (dPos.x == 0 && dPos.y == 0)
	{
		animManager.SetAnimation("amilia");
	}

	Collision(tiles);

	animManager.Update(pos);
}

Player::Player(Vector2 pos, Rectangle hitbox, float speed)
	:Entity(pos, hitbox, speed)
{
	animManager = Animation("amilia");

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
