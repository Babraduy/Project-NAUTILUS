#include "Entity.h"

Entity::Entity(Vector2 pos, Rectangle hitbox, const char* filename, float speed)
	: pos(pos), hitbox(hitbox), speed(speed), dPos({0,0})
{
	this->hitbox.x += pos.x;
	this->hitbox.y += pos.y;
	textures.push_back(LoadTexture(filename));

	if (hitbox.width == 0)
	{
		this->hitbox.width = textures[0].width;
	}

	if (hitbox.height == 0)
	{
		this->hitbox.height = textures[0].height;
	}
}

Entity::Entity(Vector2 pos, Rectangle hitbox, vector<Texture2D> frames, float speed)
	: pos(pos), hitbox(hitbox), speed(speed), dPos({ 0,0 })
{
	this->hitbox.x += pos.x;
	this->hitbox.y += pos.y;

	if (hitbox.width == 0)
	{
		this->hitbox.width = frames[0].width;
	}

	if (hitbox.height == 0)
	{
		this->hitbox.height = frames[0].height;
	}
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
