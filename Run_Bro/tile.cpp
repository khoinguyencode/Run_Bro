#include "Tile.h"

Tile::Tile(int p_x, int p_y, int p_type) : Entity(x, y, tex) {
    box.x = p_x;
    box.y = p_y;

    box.w = TILE_WIDTH;
    box.h = TILE_HEIGHT;

    type = p_type;
}

void Tile::render(SDL_Rect& camera, RenderWindow& p_renderwindow) {
    //Kiem tra va cham neu tile o tren man hinh
    if (p_renderwindow.checkCollision(camera, box))
        p_renderwindow.renderTile(*this, p, camera);
}

int Tile::getType()
{
    return type;
}

SDL_Rect Tile::getBox()
{
    return box;
}