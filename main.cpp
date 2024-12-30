#include <iostream>
#include <vector>
#include "raylib.h"

#include "Player.h"
#include "Map.h"

#define START_WIDTH 1280
#define START_HEIGHT 720

using namespace std;

int main()
{
	InitWindow(START_WIDTH, START_HEIGHT, "Project NAUTILUS");
	SetTargetFPS(144);
	SetExitKey(0);

    int width = 1280, height = 720;

    Map map("test1.json");
    float tileSize = map.tileSize;

    Player player({ tileSize,tileSize }, { 0, 0, 0, tileSize }, 100);

    Camera2D camera;
    camera.rotation = 0;
    camera.zoom = 4;

    Rectangle cameraRect = { 0 };

    vector<Tile> visibleTiles = map.GetNearbyTiles(cameraRect);

    RenderTexture2D renderTexture = LoadRenderTexture(GetRenderWidth(), GetRenderHeight());

    /* Scale up the window */
    SetWindowSize(width, height);
    SetWindowPosition(GetMonitorWidth(GetCurrentMonitor()) / 2.0f - width / 2.0f, GetMonitorHeight(GetCurrentMonitor()) / 2.0f - height / 2.0f);

    /* Main loop */
	while (!WindowShouldClose())
	{
        if (IsKeyPressed(KEY_F10))
        {
            if (IsWindowFullscreen())
            {
                SetWindowSize(width, height);
            }
            else
            {
                SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
            }

            ToggleFullscreen();
        }

        /* Update camera*/
        Vector2 playerCenter = {
            player.pos.x + player.hitbox.width / 2.0f,
            player.pos.y + player.hitbox.height / 2.0f
        };

        camera.target.x = clamp(playerCenter.x, START_WIDTH / (2.0f * camera.zoom), map.size.x * tileSize - START_WIDTH / (2.0f * camera.zoom));
        camera.target.y = clamp(playerCenter.y, START_HEIGHT / (2.0f * camera.zoom), map.size.y * tileSize - START_HEIGHT / (2.0f * camera.zoom));

        camera.offset = { START_WIDTH / 2.0f, START_HEIGHT / 2.0f };

        cameraRect = { camera.target.x - START_WIDTH / (2.0f * camera.zoom),
                       camera.target.y - START_HEIGHT / (2.0f * camera.zoom),
                       START_WIDTH + player.hitbox.x/2.0f,
                       START_HEIGHT + player.hitbox.y / 2.0f };

        visibleTiles = map.GetNearbyTiles(cameraRect);


        /* Render the image */
		BeginTextureMode(renderTexture);

        BeginMode2D(camera);

		ClearBackground(BLACK);

		player.Update(map.GetNearbyTiles({player.pos.x - tileSize, player.pos.y - tileSize, tileSize * 3, tileSize * 3}));

		for (Tile tile : visibleTiles)
		{
			tile.Draw();
		}

        EndMode2D();

		EndTextureMode();


        /* Scale up the image */
        BeginDrawing();
        DrawTexturePro(
            renderTexture.texture,
            Rectangle{ 0, 0, float(renderTexture.texture.width), float(-renderTexture.texture.height) },
            Rectangle{ 0, 0, float(GetRenderWidth()), float(GetRenderHeight()) },
            Vector2{ 0, 0 },
            0,
            WHITE);

        EndDrawing();
	}

    Animation::ClearTextureCache();

	CloseWindow();

	return 0;
}
