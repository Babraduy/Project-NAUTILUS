#include "Entity.h"

Entity::Entity(Vector2 pos, Rectangle hitbox, const char* filename, Vector2 scale, float speed)
	: pos(pos), hitbox(hitbox), scale(scale), speed(speed)
{
	img = LoadImage(filename);
	texture = LoadTextureFromImage(img);
}

Entity::~Entity()
{
	UnloadTexture(texture);
	UnloadImage(img);
}

void Entity::Draw()
{
	DrawTexturePro(texture, { 0,0,(float)texture.width,(float)texture.height },
		{ pos.x, pos.y,(float)texture.width * scale.x, (float)texture.height * scale.y },
		{ (float)texture.width / 2.0f, (float)texture.height / 2.0f }, 0, WHITE);
}
