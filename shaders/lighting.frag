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

#version 330 core

#define MAX_LIGHTS 64

in vec2 texCoord;
in vec3 FragPos;

out vec4 FragColor;

struct Light {
	int enabled;
	vec2 pos;
	vec4 color;
};

uniform sampler2D tex0;
uniform Light lights[MAX_LIGHTS];

void main()
{
    vec4 texColor = texture(tex0, texCoord);

    float constant = 1.0;
    float linear = 0.001;
    float quadratic = 0.0011;

	vec3 ambient = vec3(0.1f);

	vec3 color = vec3(0);

	for (int i=0; i<lights.length(); i++)
	{
        if (lights[i].enabled == 0) continue;

		float distance = length(lights[i].pos - FragPos.xy);

		float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

		color += (lights[i].color.rgb * attenuation) * texColor.rgb * lights[i].color.a;
	}

	color += ambient*texColor.rgb;

	FragColor = vec4(clamp(color,0.0,1.0), texColor.a);
}