#include <iostream>
#include <vector>
#include "raylib.h"

#include "Player.h"

#define WIDTH 800
#define HEIGHT 600
#define TILE 50

using namespace std;

struct Grid
{
    unordered_map<int, vector<Tile>> cells;

    int getCellIndex(int x, int y)
    {
        return (y / TILE) * 10000 + (x / TILE);
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
	InitWindow(WIDTH, HEIGHT, "Project NAUTILUS");
	SetTargetFPS(144);
	SetExitKey(0);

	Player player({ 0,0 }, { 0,0,0,0 }, "img/character/frame1.png", {5,5}, 200);

	Grid grid;

	grid.addTile(Tile({ 400,400,TILE,TILE }, SOLID, "img/ph_roomtile.png"));
	grid.addTile(Tile({ 450,400,TILE,TILE }, SOLID, "img/ph_roomtile.png"));
	grid.addTile(Tile({ 500,400,TILE,TILE }, SOLID, "img/ph_roomtile.png"));
	grid.addTile(Tile({ 550,400,TILE,TILE }, SOLID, "img/ph_roomtile.png"));
	grid.addTile(Tile({ 600,400,TILE,TILE }, SOLID, "img/ph_roomtile.png"));

    grid.addTile(Tile({ 400,350,TILE,TILE }, SOLID, "img/ph_roomtile.png"));
    grid.addTile(Tile({ 450,300,TILE,TILE }, SOLID, "img/ph_roomtile.png"));
    grid.addTile(Tile({ 500,250,TILE,TILE }, SOLID, "img/ph_roomtile.png"));
    grid.addTile(Tile({ 550,200,TILE,TILE }, SOLID, "img/ph_roomtile.png"));
    grid.addTile(Tile({ 600,150,TILE,TILE }, SOLID, "img/ph_roomtile.png"));

	vector<Tile> visibleTiles = grid.getNearbyTiles(player.camera);

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(BLACK);

		player.Update(grid.getNearbyTiles({player.pos.x- TILE, player.pos.y- TILE, TILE *3, TILE *3}));

		for (Tile tile : visibleTiles)
		{
			tile.Draw();
		}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
