#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include "raylib.h"

using namespace std;

class Animation
{
private:
	vector<Texture2D> frames;
	unsigned int currentFrame;
	float frameDuration, elapsedTime;
	bool loop, isFinished;

public:
	int flipX;
	int flipY;

	Animation(vector<Texture2D>& frames, float frameDuration, bool loop = true);
	Animation() {}

	void Update(Vector2 pos);
	void SetFrames(vector<Texture2D>& frames, float frameDuration, bool loop = true);
};

