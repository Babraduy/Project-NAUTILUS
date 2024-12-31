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

	if (textureCache.find(filename) == textureCache.end())
	{
		cout << "1 " << filename << endl;
		textureCache[filename] = LoadTexture(spriteSheetFilename.c_str());
	}

	spriteSheet = textureCache[filename];
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
		{ (float)frame.x, (float)frame.y, (float)frame.w*flipX, (float)frame.h * flipY },
		{ pos.x, pos.y,(float)frame.w,(float)frame.h },
		{ 0,0 },
		0,
		WHITE);
}

void Animation::SetAnimation(string animation)
{
	if (animation != currentAnimation)
	{
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

void Animation::ClearTextureCache()
{
	for (auto& cache : textureCache)
	{
		UnloadTexture(cache.second);
	}
	textureCache.clear();
}
