#include <iostream>
#include <vector>
#include "raylib.h"

#include "Player.h"
#include "Map.h"

#define START_WIDTH 320
#define START_HEIGHT 180

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
    camera.offset = { START_WIDTH / 2.0f - player.hitbox.x / 2.0f, START_HEIGHT / 2.0f - player.hitbox.y / 2.0f };
    camera.rotation = 0;
    camera.zoom = 1;

    Rectangle cameraRect = { 0 };

    vector<Tile> visibleTiles = map.GetNearbyTiles(cameraRect);

    RenderTexture2D renderTexture = LoadRenderTexture(GetRenderWidth(), GetRenderHeight());

    SetWindowSize(width, height);

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


        // Update camera
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


		BeginTextureMode(renderTexture);

        BeginMode2D(camera);

		ClearBackground(BLACK);

		player.Update(map.GetNearbyTiles({player.pos.x - tileSize, player.pos.y - tileSize, tileSize * 3, tileSize * 3}));

        vector<Tile> playerTiles = map.GetNearbyTiles({ player.pos.x - tileSize, player.pos.y - tileSize, tileSize * 3, tileSize * 3 });

		for (Tile tile : visibleTiles)
		{
			tile.Draw();
		}

        EndMode2D();

		EndTextureMode();


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

	CloseWindow();

	return 0;
}
