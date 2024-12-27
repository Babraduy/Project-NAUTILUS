#include <iostream>
#include <vector>
#include "raylib.h"

#include "Player.h"

#define START_WIDTH 320
#define START_HEIGHT 180

using namespace std;

float tileSize = 18;

struct Grid
{
    unordered_map<int, vector<Tile>> cells;

    int getCellIndex(int x, int y)
    {
        return (y /(int) tileSize) * 10000 + (x / (int)tileSize);
    }

    void addTile(const Tile& tile)
    {
        int topLeft = getCellIndex(tile.x, tile.y);
        int bottomRight = getCellIndex(tile.x + tile.width, tile.y + tile.height);


        for (int y = topLeft / 10000; y <= bottomRight / 10000; y++)
        {
            for (int x = topLeft % 10000; x <= bottomRight % 10000; x++)
            {
                cells[y * 10000 + x].push_back(tile);
            }
        }
    }

    vector<Tile> getNearbyTiles(const Rectangle& area)
    {
        int topLeft = getCellIndex(area.x, area.y);
        int bottomRight = getCellIndex(area.x + area.width, area.y + area.height);

        vector<Tile> result;

        for (int y = topLeft / 10000; y <= bottomRight / 10000; y++)
        {
            for (int x = topLeft % 10000; x <= bottomRight % 10000; x++)
            {
                auto it = cells.find(y * 10000 + x);
                if (it != cells.end())
                {
                    result.insert(result.end(), it->second.begin(), it->second.end());
                }
            }
        }

        return result;
    }
};

int main()
{
	InitWindow(START_WIDTH, START_HEIGHT, "Project NAUTILUS");
	SetTargetFPS(144);
	SetExitKey(0);

    int width = 1280, height = 720;

    Player player({ 0,0 }, { 0, 0, 0, tileSize }, 100);

	Grid grid;

	grid.addTile(Tile({ 40,180-tileSize,tileSize,tileSize }, SOLID, "img/ph_roomtile.png"));
	grid.addTile(Tile({ 40+tileSize,180 - tileSize,tileSize,tileSize }, SOLID, "img/ph_roomtile.png"));
	grid.addTile(Tile({ 40+tileSize*2,180 - tileSize,tileSize,tileSize }, SOLID, "img/ph_roomtile.png"));
    grid.addTile(Tile({ 40+tileSize*3,180 - tileSize,tileSize,tileSize }, SOLID, "img/ph_roomtile.png"));
	grid.addTile(Tile({ 40+tileSize*4,180 - tileSize,tileSize,tileSize }, SOLID, "img/ph_roomtile.png"));

    grid.addTile(Tile({ 40,180 -tileSize*2,tileSize,tileSize }, SOLID, "img/ph_roomtile.png"));
    grid.addTile(Tile({ 40+tileSize,180 - tileSize*3,tileSize,tileSize }, SOLID, "img/ph_roomtile.png"));
    grid.addTile(Tile({ 40+tileSize*2,180 - tileSize*4,tileSize,tileSize }, SOLID, "img/ph_roomtile.png"));
    grid.addTile(Tile({ 40+tileSize*3,180 - tileSize*5,tileSize,tileSize }, SOLID, "img/ph_roomtile.png"));
    grid.addTile(Tile({ 40+tileSize*4,180 - tileSize*6,tileSize,tileSize }, SOLID, "img/ph_roomtile.png"));

    vector<Tile> visibleTiles = grid.getNearbyTiles(player.camera);

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



		BeginTextureMode(renderTexture);

		ClearBackground(BLACK);

		player.Update(grid.getNearbyTiles({player.pos.x - tileSize, player.pos.y - tileSize, tileSize * 3, tileSize * 3}));

        vector<Tile> playerTiles = grid.getNearbyTiles({ player.pos.x - tileSize, player.pos.y - tileSize, tileSize * 3, tileSize * 3 });

		for (Tile tile : visibleTiles)
		{
			tile.Draw();
		}

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
