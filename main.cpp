#include <iostream>
#include "raylib.h"

#include "Player.h"

#define WIDTH 800
#define HEIGHT 600

using namespace std;

int main()
{
	InitWindow(WIDTH, HEIGHT, "Project NAUTILUS");
	SetTargetFPS(144);
	SetExitKey(0);

	// Load textures
	Player player({ 0,0 }, { 0,0,0,0 }, "img/character/frame1.png", {5,5});

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(BLACK);

		player.Update();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
