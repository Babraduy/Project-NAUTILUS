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

in vec3 aPos;
in vec2 aTex;

uniform mat4 mvp;

out vec2 texCoord;
out vec3 FragPos;

void main()
{
    FragPos = aPos;
    gl_Position = mvp * vec4(aPos, 1.0);

    texCoord = aTex;
}