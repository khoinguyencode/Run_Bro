#include "Tile.h"
#include <fstream>
using namespace std;

Tile::Tile(float p_x, float p_y, SDL_Texture* p_tex, int p_type) : Entity(p_x, p_y, p_tex) {
    box.x = p_x;
    box.y = p_y;

    box.w = TILE_WIDTH;
    box.h = TILE_HEIGHT;

    type = p_type;
}

void Tile::setType(int p_type) {
    type = p_type;
}

int Tile::getType() {
    return type;
}

SDL_Rect Tile::getBox() {
    return box;
}