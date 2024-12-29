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
	animManager = Animation("player_walk");

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
