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

    UpdateLight(shader);

	lightsCount++;
}

Light::Light(Vector2 pos, Color color, Shader shader)
{
    this->enabled = 1;
    this->pos = pos;
    this->color.x = color.r;
    this->color.y = color.g;
    this->color.z = color.b;
    this->color.w = color.a;

    enabledLoc = GetShaderLocation(shader, TextFormat("lights[%i].enabled", lightsCount));
    posLoc = GetShaderLocation(shader, TextFormat("lights[%i].pos", lightsCount));
    colorLoc = GetShaderLocation(shader, TextFormat("lights[%i].color", lightsCount));

    UpdateLight(shader);

    lightsCount++;
}

void Light::UpdateLight(Shader shader)
{
    SetShaderValue(shader, enabledLoc, &enabled, SHADER_UNIFORM_INT);
    SetShaderValue(shader, posLoc, &pos, SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, colorLoc, &color, SHADER_UNIFORM_VEC4);
}

Vector4 ParseColor(const std::string & hex) {
    if (hex.empty() || hex[0] != '#' || hex.length() < 7) return {1,1,1,1};

    int r, g, b, a = 255;
    sscanf_s(hex.c_str(), "#%02x%02x%02x", &r, &g, &b);
    
    if (hex.length() == 9) {
        sscanf_s(hex.c_str(), "#%02x%02x%02x%02x", &a, &r, &g, &b);
    }

    return { r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f };
}

float SineWave(float time, float freq, float ampl, float off)
{
    return ampl * sin(freq * time) + off;
}
