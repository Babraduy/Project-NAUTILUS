/*  Project NAUTILUS
    Copyright (C) 2024-2025  Babraduy

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
