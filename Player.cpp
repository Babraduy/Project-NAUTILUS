#include "Player.h"

void Player::Update()
{
	if (IsKeyDown(KEY_W))
	{
		pos.y--;
	}
	if (IsKeyDown(KEY_A))
	{
		pos.x--;
	}
	if (IsKeyDown(KEY_S))
	{
		pos.y++;
	}
	if (IsKeyDown(KEY_D))
	{
		pos.x++;
	}

	this->Draw();
}

Player::Player(Vector2 pos, Rectangle hitbox, const char* filename, Vector2 scale, float speed)
	:Entity(pos, hitbox, filename, scale, speed)
{

}

Player::~Player()
{
	
}
