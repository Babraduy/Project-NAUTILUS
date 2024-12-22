#include <iostream>
#include "raylib.h"

#define WIDTH 800
#define HEIGHT 600

int main()
{
	InitWindow(WIDTH, HEIGHT, "Project NAUTILUS");
	SetTargetFPS(144);

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(BLACK);

		DrawCircle(WIDTH / 2, HEIGHT / 2, 50, WHITE);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
