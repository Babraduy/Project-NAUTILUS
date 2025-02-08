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

#include "Map.h"

Map::Map(string filename, Shader shader)
{
    Load(filename, shader);
}

void Map::Load(string filename, Shader shader)
{
    filename = "maps/" + filename;

    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "File " << filename << " doesn't exist\n";
        return;
    }

    json jsonData;
    file >> jsonData;

    tileSize = jsonData["tileheight"];

    auto& tileset = jsonData["tilesets"][0];

    for (int i = 1; i <= tileset["columns"]; i++)
    {
        string name = "img/" + tileset["name"].get<string>() + ".png";
        tileIDs[i] = Tile({ 0,0,tileSize,tileSize }, SOLID, name.c_str(), {(i - 1) * tileSize, 0, tileSize, tileSize});
    }

    for (auto& data : jsonData["layers"])
    {
        int width = data["width"];
        int height = data["height"];

        this->size = { (float)width, (float)height };

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (data["data"][y * width + x] == 0) continue;

                Tile tile = tileIDs[data["data"][y*width + x]];
                tile.x = x * tileSize;
                tile.y = y * tileSize;

                for (auto& prop : data["properties"])
                {
                    if (prop["name"] == "type")
                    {
                        auto value = prop["value"].get<string>();

                        if (value == "solid")
                        {
                            tile.type = SOLID;
                        }
                        if (value == "walkable")
                        {
                            tile.type = WALKABLE;
                        }
                        if (value == "trigger_dialogue_destroyable")
                        {
                            tile.type = TRIGGER_DIALOGUE_DESTROYABLE;
                        }
                        if (value == "light")
                        {
                            tile.type = LIGHT;
                        }
                    }
                    if (prop["name"] == "dialogue")
                    {
                        tile.triggerValue = prop["value"].get<string>();
                    }
                    if (prop["name"] == "color")
                    {
                        tile.colorValue = ParseColor(prop["value"].get<string>());
                    }
                }

                tile.layer = data["id"];

                AddTile(tile);

                if (tile.type == LIGHT)
                {
                    lights.push_back(Light({ tile.x + tileSize/2.0f, tile.y + tileSize/2.0f }, tile.colorValue, shader));
                }
            }
        }
    }
}

int Map::GetCellIndex(int x, int y)
{
    return (y / (int)tileSize) * 10000 + (x / (int)tileSize);
}

void Map::AddTile(const Tile& tile)
{
    cells[GetCellIndex(tile.x, tile.y)].push_back(tile);
}

void Map::RemoveTile(Tile tile)
{
    auto it = cells.find(GetCellIndex(tile.x, tile.y));
    if (it != cells.end())
    {
        it->second.erase(remove(it->second.begin(), it->second.end(), tile), it->second.end());

        if (it->second.empty())
        {
            cells.erase(it);
        }
    }
}

vector<Tile> Map::GetNearbyTiles(const Rectangle& area)
{
    int topLeft = GetCellIndex(area.x, area.y);
    int bottomRight = GetCellIndex(area.x + area.width, area.y + area.height);

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