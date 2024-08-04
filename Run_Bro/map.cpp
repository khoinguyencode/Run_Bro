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
    else{
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
            if (x >= getX() + LEVEL_WIDTH) {
                x = getX();
                y += TILE_HEIGHT;
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