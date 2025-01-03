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

#include "Dialogue.h"

Dialogue::Dialogue(string index, Font font, float fontSize, float typingSpeed)
	:padding(10), fontSize(fontSize)
{
	LoadText(index, font, typingSpeed);
}

void Dialogue::LoadText(string index, Font font, float typingSpeed)
{
	this->font = font;
	this->typingSpeed = typingSpeed;

	isFinished = isClosed = false;

	visibleChars = 0;
	elapsedTime = 0.0f;

	ifstream file("config/dialogues.json");

	if (!file.is_open())
	{
		text = "File 'config/dialogues.json' does not exist";
	}
	else
	{
		json jsonData;
		file >> jsonData;

		if (jsonData.contains(index))
		{
			text = jsonData[index];
		}
		else
		{
			text = "Index " + index + " does not exist";
		}
	}
}

void Dialogue::Update(int WIDTH, int HEIGHT)
{

	if (!isClosed)
	{
		if (IsKeyPressed(KEY_X))
		{
			isFinished = true;

			visibleChars = strlen(text.c_str());
		}
		if (isFinished && IsKeyPressed(KEY_Z)) isClosed = true;

		if (!isFinished)
		{
			elapsedTime += GetFrameTime();

			visibleChars = int(elapsedTime * typingSpeed);

			if (visibleChars > strlen(text.c_str())) isFinished = true;
		}

		DrawRectangleRec({(float) padding, HEIGHT / 2.0f + padding, (float)WIDTH - padding, HEIGHT / 2.0f - padding }, BLACK);

		DrawTextRec(font, TextSubtext(text.c_str(), 0, visibleChars), { padding * 2.0f, HEIGHT / 2.0f + padding * 2.0f, WIDTH - padding * 2.0f, HEIGHT / 2.0f - padding * 2.0f }, 5, false, WHITE);
	}
}

void Dialogue::DrawTextRec(Font font, const char* text, Rectangle rec, float spacing, bool wordWrap, Color tint)
{
	float textWidth = 0;
	float textHeight = fontSize;

	Vector2 position = { rec.x, rec.y };

	for (int i = 0; text[i] != '\0'; i++) {
		char letter[2] = { text[i], '\0' };
		Vector2 letterSize = MeasureTextEx(font, letter, fontSize, spacing);

		if (wordWrap && text[i] == ' ' && (textWidth + letterSize.x > rec.width)) {
			position.x = rec.x;
			position.y += textHeight;
			textWidth = 0;
		}

		if (textWidth + letterSize.x > rec.width) {
			position.x = rec.x;
			position.y += textHeight;
			textWidth = 0;
		}

		DrawTextEx(font, letter, position, fontSize, spacing, tint);
		position.x += letterSize.x + spacing;
		textWidth += letterSize.x + spacing;
	}
}
