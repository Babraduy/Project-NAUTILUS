#include "Light.h"

Light::Light(Vector2 pos, Vector4 color, Shader shader)
{
	this->enabled = 1;
	this->pos = pos;
	this->color = color;

	enabledLoc = GetShaderLocation(shader, TextFormat("lights[%i].enabled", lightsCount));
	posLoc = GetShaderLocation(shader, TextFormat("lights[%i].pos", lightsCount));
	colorLoc = GetShaderLocation(shader, TextFormat("lights[%i].color", lightsCount));

	SetShaderValue(shader, enabledLoc, &enabled, SHADER_UNIFORM_INT);
	SetShaderValue(shader, posLoc, &pos, SHADER_UNIFORM_VEC2);
	SetShaderValue(shader, colorLoc, &color, SHADER_UNIFORM_VEC4);

	lightsCount++;
}
