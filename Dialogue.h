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

#pragma once

#include <iostream>
#include <raylib.h>
#include <nlohmann/json.hpp>
#include <fstream>

using namespace std;
using namespace nlohmann;

class Dialogue
{
private:
	int padding;
	bool isFinished;
	float elapsedTime;
	int visibleChars;

public:
	string text;
	Font font;
	float typingSpeed, fontSize; // symbols per second
	bool isClosed;

	Dialogue(string index, Font font = GetFontDefault(), float fontSize = 1.0f, float typingSpeed = 10.0f);
	Dialogue() {}

	void LoadText(string index, Font font = GetFontDefault(), float typingSpeed = 10.0f);
	void Update(int WIDTH, int HEIGHT);
	void DrawTextRec(Font font, const char* text, Rectangle rec, float spacing, bool wordWrap, Color tint);

};

