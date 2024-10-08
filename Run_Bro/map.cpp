#include "Map.h"
#include <fstream>
#include <iostream>
using namespace std;

Map::Map(float p_x, float p_y, const char* p_filePath, SDL_Texture* p_tileTex)
    :x(p_x), y(p_y)
{
    bool tilesLoaded = true;
    int x = getX(), y = getY();
    ifstream map(p_filePath);

    if (map.fail()) {
        printf("Unable to load map file!\n");
        tilesLoaded = false;
    }
    else {
        for (int i = 0; i < TOTAL_TILES; ++i) {
            int tileType = -1;

            map >> tileType;
            if (map.fail()) {
                printf("Error loading map: Unexpected end of file!\n");
                tilesLoaded = false;
                break;
            }

            if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES)) {
                Tile* tile = new Tile(x, y, p_tileTex, tileType);
                tiles.push_back(tile);
            }
            else {
                printf("Error loading map: Invalid tile type at %d!\n", i);
                tilesLoaded = false;
                break;
            }

            x += TILE_WIDTH;
            if (x >= getX() + MAP_WIDTH) {
                x = getX();
                y += TILE_HEIGHT;
            }
        }
    }
    map.close();
}

void Map::setX(float p_x) {
    x = p_x;
    for (int i = 0; i < tiles.size(); i++) {
        int cols = i / 21;
        int rows = (i - cols * 21) * TILE_WIDTH + getX();
        tiles.at(i)->setX(rows);
    }
}
void Map::setMap(Map& p_map) {
    x = p_map.getX() + MAP_WIDTH;
    for (int i = 0; i < tiles.size(); i++) {
        int cols = i / 21;
        int rows = (i - cols * 21) * TILE_WIDTH + getX();
        tiles.at(i)->setX(rows);
    }
}

void Map::setTilesType(const char* p_filePath) {
    bool tilesLoaded = true;
    int n = x, m = y;
    ifstream map(p_filePath);

    if (map.fail()) {
        printf("Unable to load map file!\n");
        tilesLoaded = false;
    }
    else
    {
        for (int i = 0; i < TOTAL_TILES; ++i) {
            int tileType = -1;

            map >> tileType;
            if (map.fail()) {
                printf("Error loading map: Unexpected end of file!\n");
                tilesLoaded = false;
                break;
            }
            if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES)) {
                tiles[i]->setType(tileType);
            }
            else
            {
                printf("Error loading map: Invalid tile type at %d!\n", i);
                tilesLoaded = false;
                break;
            }
            n += TILE_WIDTH;

            //den cuoi map
            if (n >= x + MAP_WIDTH) {
                //xuong dong
                n = x;
                m += TILE_HEIGHT;
            }
        }
    }
    map.close();
}

void Map::render(SDL_Rect p_tileClips[], SDL_Rect& p_camera, RenderWindow& p_renderwindow) {
    for (int i = 0; i < tiles.size(); i++) {
        p_renderwindow.renderTile(*tiles[i], p_tileClips[tiles[i]->getType()], p_camera);
    }
}

vector<Tile*> Map::getTiles() {
    return tiles;
}

float Map::getX() {
    return x;
}

float Map::getY() {
    return y;
}

vector<int> Map::getMonsterPos() {
    return monsterPos;
}

void Map::setMonsterPos(vector<int>& p_monsterPos) {
    monsterPos = p_monsterPos;
}