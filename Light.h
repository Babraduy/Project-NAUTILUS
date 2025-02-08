#pragma once

#define MAX_LIGHTS 64

#include "raylib.h"

static int lightsCount = 0;

class Light
{
public:
	int enabled;
	Vector2 pos;
	Vector4 color;

	int enabledLoc, posLoc, colorLoc;

	Light() {}
	Light(Vector2 pos, Vector4 color, Shader shader);
};