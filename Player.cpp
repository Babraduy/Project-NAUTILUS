#include "Player.h"

void Player::Update(vector<Tile> tiles)
{
	dPos = { 0,0 };

	if (IsKeyDown(KEY_W))
	{
		dPos.y-= speed * GetFrameTime();

		walkAnim.SetFrames(back, 0.2f);
	}
	if (IsKeyDown(KEY_A))
	{
		dPos.x-= speed * GetFrameTime();

		walkAnim.SetFrames(side, 0.2f);
		walkAnim.flipX = -1;
	}
	if (IsKeyDown(KEY_S))
	{
		dPos.y+=speed * GetFrameTime();

		walkAnim.SetFrames(front, 0.2f);
	}
	if (IsKeyDown(KEY_D))
	{
		dPos.x+=speed * GetFrameTime();

		walkAnim.SetFrames(side, 0.2f);
		walkAnim.flipX = 1;
	}

	Collision(tiles);

	walkAnim.Update(pos);
}

Player::Player(Vector2 pos, Rectangle hitbox, vector<Texture2D>& front, vector<Texture2D>& side, vector<Texture2D>& back, float speed)
	:Entity(pos, hitbox, front, speed), front(front), side(side), back(back)
{
	camera = { 0,0,(float)GetRenderWidth(), (float)GetRenderHeight() };

	walkAnim = Animation(front, 0.2f);
}

Player::~Player() { }
