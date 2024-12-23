#include "Player.h"

void Player::Update(vector<Tile> tiles)
{
	dPos = { 0,0 };

	if (IsKeyDown(KEY_W))
	{
		dPos.y-= speed * GetFrameTime();
	}
	if (IsKeyDown(KEY_A))
	{
		dPos.x-= speed * GetFrameTime();
	}
	if (IsKeyDown(KEY_S))
	{
		dPos.y+=speed * GetFrameTime();
	}
	if (IsKeyDown(KEY_D))
	{
		dPos.x+=speed * GetFrameTime();
	}

	Collision(tiles);

	this->Draw();
}

Player::Player(Vector2 pos, Rectangle hitbox, const char* filename, Vector2 scale, float speed)
	:Entity(pos, hitbox, filename, scale, speed)
{
	camera = { 0,0,(float)GetRenderWidth(), (float)GetRenderHeight() };
}

Player::~Player() { }
