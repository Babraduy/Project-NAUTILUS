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

#pragma once

#include <nlohmann/json.hpp>
#include <fstream>

#include "Tile.h"
#include "Light.h"

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

    vector<Light> lights;

    Map(string filename, Shader shader);

    void Load(string filename, Shader shader);

    int GetCellIndex(int x, int y);
    void AddTile(const Tile& tile);
    void RemoveTile(Tile tile);
    vector<Tile> GetNearbyTiles(const Rectangle& area);
};