#include "Map.h"
#include <fstream>
using namespace std;

Map::Map(const char* p_filePath, SDL_Texture* p_tileTex) {
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

vector<Tile*> Map::getTiles() {
    return tiles;
}

float Map::getX() {
	return x;
}

float Map::getY() {
	return y;
}