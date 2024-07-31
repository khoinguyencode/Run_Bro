#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Renderwindow.h"
#include "Entity.h"

const int TILE_WIDTH = 64;
const int TILE_HEIGHT = 64;

class Tile : public Entity{
public:
	Tile(int x, int y, int tileType);
	void render(SDL_Rect& camera, RenderWindow& p_renderwindow);
	int getType();

	//get collison box
	SDL_Rect getBox();

private:
	SDL_Rect box;
	int type;
};

