#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <nlohmann/json.hpp>
#include "raylib.h"

using namespace std;
using namespace nlohmann;

struct Frame
{
	int x, y, w, h;
};

class Animation
{
private:
	Texture2D spriteSheet;
	string currentAnimation;
	unsigned int currentFrame;
	float frameDuration, elapsedTime;
	bool loop, isFinished;

public:
	vector<Frame> frames;
	int flipX;
	int flipY;

	Animation(string animation);
	Animation() {}

	void LoadFrames(string filename);
	void Update(Vector2 pos);
	void SetAnimation(string animation);
};

