#include "Animation.h"

Animation::Animation(vector<Texture2D>& frames, float frameDuration, bool loop)
	:frames(frames), frameDuration(frameDuration), loop(loop), currentFrame(0), elapsedTime(0), isFinished(false), flipX(1), flipY(1)
{
}

void Animation::Update(Vector2 pos)
{
	if (!isFinished)
	{
		elapsedTime += GetFrameTime();
		if (elapsedTime >= frameDuration)
		{
			currentFrame++;
			elapsedTime = 0;

			if (currentFrame >= frames.size())
			{
				if(!loop)
				{
					isFinished = true;
					currentFrame--;
				}
				else
				{
					currentFrame = 0;
				}
			}
		}
	}

	Texture2D& texture = frames[currentFrame];

	DrawTexturePro(texture, { 0,0,(float)texture.width*flipX,(float)texture.height * flipY },
		{ pos.x, pos.y,(float)texture.width, (float)texture.height },
		{ 0,0 }, 0, WHITE);
}

void Animation::SetFrames(vector<Texture2D>& frames, float frameDuration, bool loop)
{
	if (!equal(this->frames.begin(), this->frames.end(), frames.begin(), [](const Texture2D& a, const Texture2D& b) {
		return a.id == b.id;
		}) || this->frameDuration != frameDuration || this->loop != loop)
	{
		this->frames = frames;
		this->frameDuration = frameDuration;
		this->loop = loop;

		elapsedTime = currentFrame = isFinished = 0;
	}
}