#include "Entity.h"

Entity::Entity(Vector2 pos, Rectangle hitbox, const char* filename, Vector2 scale, float speed)
	: pos(pos), hitbox(hitbox), scale(scale), speed(speed)
{
	this->hitbox.x += pos.x;
	this->hitbox.y += pos.y;

	dPos = { 0,0 };
	texture = LoadTexture(filename);

	if (hitbox.width == 0 && hitbox.height == 0)
	{
		this->hitbox.width = texture.width * scale.x;
		this->hitbox.height = texture.height * scale.y;
	}
}

Entity::~Entity()
{
	UnloadTexture(texture);
}

void Entity::Draw()
{
	DrawTexturePro(texture, { 0,0,(float)texture.width,(float)texture.height },
		{ pos.x, pos.y,(float)texture.width * scale.x, (float)texture.height * scale.y },
		{ 0, 0 }, 0, WHITE);
}

void Entity::Collision(vector<Tile> tiles)
{
	pos.x += dPos.x;
	hitbox.x += dPos.x;

	for (const Tile& tile : tiles)
	{
		if (CheckCollisionRecs(hitbox, tile))
		{
			switch (tile.type)
			{
			case SOLID:
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
				break;
			}
		}
	}

	pos.y += dPos.y;
	hitbox.y += dPos.y;

	for (const Tile& tile : tiles)
	{
		if (CheckCollisionRecs(hitbox, tile))
		{
			switch (tile.type)
			{
			case SOLID:
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
				break;
			}
		}
	}
}
