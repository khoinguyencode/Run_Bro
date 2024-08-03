#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Renderwindow.h"
#include "Entity.h"

//Tile constants
const int TILE_WIDTH = 64;
const int TILE_HEIGHT = 64;
const int TOTAL_TILES = 600;
const int TOTAL_TILE_SPRITES = 15;


class Tile : public Entity{
public:
	Tile(float p_x, float p_y, SDL_Texture* p_tex , int tileType);
	void setType(int p_type);
	int getType();
	//get collison box
	SDL_Rect getBox();
private:
	SDL_Rect box;
	int type;
};

