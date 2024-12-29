#pragma once

#include <nlohmann/json.hpp>
#include <fstream>

#include "Tile.h"

using namespace std;
using namespace nlohmann;

class Map
{
private:

public:
    float tileSize;
    unordered_map<int, vector<Tile>> cells;
    unordered_map<int, Tile> tileIDs;
    Vector2 size;

    Map(string filename);

    void Load(string filename);

    int GetCellIndex(int x, int y);
    void AddTile(const Tile& tile);
    vector<Tile> GetNearbyTiles(const Rectangle& area);
};