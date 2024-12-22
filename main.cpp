#include <iostream>
#include "raylib.h"

#define WIDTH 800
#define HEIGHT 600

int main()
{
	InitWindow(WIDTH, HEIGHT, "Project NAUTILUS");
	SetTargetFPS(144);

	// Load textures
	Image i_scroll = LoadImage("img/scroll.png");

	Texture2D scroll = LoadTextureFromImage(i_scroll);

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(BLACK);

		DrawTexturePro(scroll, {0,0,(float)scroll.width,(float)scroll.height}, { WIDTH/2, HEIGHT/2,(float)scroll.width * 5.0f, (float)scroll.height * 5.0f },{ (float)scroll.width/2.0f, (float)scroll.height/2.0f}, 0, WHITE);

		EndDrawing();
	}

	UnloadTexture(scroll);
	CloseWindow();

	return 0;
}
