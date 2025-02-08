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

#include <iostream>
#include <vector>
#include "raylib.h"

#include "Player.h"
#include "Map.h"

#define START_WIDTH 1280
#define START_HEIGHT 720

#define DEBUG_MODE false

using namespace std;

/* For smooth camera movement */
Vector2 Lerp(Vector2 start, Vector2 end, float t)
{
    return {
        start.x + t * (end.x - start.x)*GetFrameTime(),
        start.y + t * (end.y - start.y) * GetFrameTime()
    };
}

int main()
{
	InitWindow(START_WIDTH, START_HEIGHT, "Project NAUTILUS");
	SetExitKey(0);

    int width = 1280, height = 720;

    Shader lightingShader = LoadShader("shaders/lighting.vert", "shaders/lighting.frag");
    SetShaderValue(lightingShader, GetShaderLocation(lightingShader, "tex0"), 0, SHADER_UNIFORM_SAMPLER2D);

    Map map("test2.json", lightingShader);
    float tileSize = map.tileSize;

    Player player({ tileSize,tileSize }, { 0, 0, tileSize-1, tileSize-1 }, 100);

    Camera2D camera;
    camera.target = player.pos;
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

        camera.target.x = clamp(Lerp(camera.target, playerCenter, 15.f).x, START_WIDTH / (2.0f * camera.zoom), map.size.x * tileSize - START_WIDTH / (2.0f * camera.zoom));
        camera.target.y = clamp(Lerp(camera.target, playerCenter, 15.f).y, START_HEIGHT / (2.0f * camera.zoom), map.size.y * tileSize - START_HEIGHT / (2.0f * camera.zoom));

        camera.offset = { START_WIDTH / 2.0f, START_HEIGHT / 2.0f };

        cameraRect = { camera.target.x - START_WIDTH / (2.0f * camera.zoom),
                       camera.target.y - START_HEIGHT / (2.0f * camera.zoom),
                       START_WIDTH + player.hitbox.x/2.0f,
                       START_HEIGHT + player.hitbox.y / 2.0f };

        visibleTiles = map.GetNearbyTiles(cameraRect);

        /*for (Light l : map.lights)
        {
            l.color.w = SineWave(GetTime(), 10, 0.5, 0.4);
            l.UpdateLight(lightingShader);
        }*/

        /* Render the image */
		BeginTextureMode(renderTexture);

        BeginMode2D(camera);
        
        BeginShaderMode(lightingShader);

		ClearBackground(BLACK);

        for (Tile tile : visibleTiles)
        {
            if (tile.layer == 1)
            {
                if (tile.type == TRIGGER_DIALOGUE_DESTROYABLE || tile.type == TRIGGER_DIALOGUE || tile.type == LIGHT)
                {
                    if (DEBUG_MODE)
                    {
                        tile.Draw();
                    }
                }
                else
                {
                    tile.Draw();
                }
            }
        }

        player.Update(map);

		for (Tile tile : visibleTiles)
		{
            if (tile.layer != 1)
            {
                if (tile.type == TRIGGER_DIALOGUE_DESTROYABLE || tile.type == TRIGGER_DIALOGUE || tile.type == LIGHT)
                {
                    if (DEBUG_MODE)
                    {
                        tile.Draw();
                    }
                }
                else
                {
                    tile.Draw();
                }
            }
		}

        EndShaderMode();

        EndMode2D();

        DrawFPS(0, 0);
        player.dialogueManager.Update(START_WIDTH, START_HEIGHT);

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

    UnloadShader(lightingShader);

	CloseWindow();

	return 0;
}
