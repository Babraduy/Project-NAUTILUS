#include "Animation.h"

Animation::Animation(string animation)
	:flipX(1), flipY(1)
{
	SetAnimation(animation);
}

void Animation::LoadFrames(string filename)
{
	ifstream file(filename);

	if (!file.is_open())
	{
		cout << "File " << filename << " doesn't exist\n";
		return;
	}

	json jsonData;
	file >> jsonData;

	frames.clear();

	for (auto& frameData : jsonData["frames"])
	{
		const auto& frame = frameData["frame"];

		Frame f;
		f.x = frame["x"];
		f.y = frame["y"];
		f.w = frame["w"];
		f.h = frame["h"];
		frames.push_back(f);
	}

	string spriteSheetFilename = "img/" + jsonData["meta"]["image"].get<string>();

	spriteSheet = LoadTexture(spriteSheetFilename.c_str());
}

void Animation::Update(Vector2 pos)
{
	elapsedTime += GetFrameTime();

	if (elapsedTime >= frameDuration && !isFinished)
	{
		elapsedTime = 0;
		currentFrame++;
		if (currentFrame >= frames.size())
		{
			if (loop)
			{
				currentFrame = 0;
			}
			else
			{
				currentFrame--;
				isFinished = true;
			}
		}
	}

	Frame& frame = frames[currentFrame];

	DrawTexturePro(
		spriteSheet,
		{ (float)frame.x, (float)frame.y, (float)frame.w, (float)frame.h },
		{ pos.x, pos.y,(float)frame.w,(float)frame.h },
		{ 0,0 },
		0,
		WHITE);
}

void Animation::SetAnimation(string animation)
{
	if (animation != currentAnimation)
	{
		UnloadTexture(spriteSheet);

		currentAnimation = animation;
		isFinished = false;

		currentFrame = 0;
		elapsedTime = 0;

		ifstream file("config/animations.json");
		json jsonData;
		file >> jsonData;

		auto& data = jsonData["animations"][animation];

		loop = data["loop"];
		frameDuration = data["frameDuration"];

		string filename = "config/" + data["filename"].get<string>();

		LoadFrames(filename);
	}
}
