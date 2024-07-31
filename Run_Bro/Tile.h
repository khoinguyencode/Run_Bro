#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Renderwindow.h"
#include "Entity.h"

//Tile constants
const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 80;
const int TOTAL_TILES = 192;
const int TOTAL_TILE_SPRITES = 12;

//The different tile sprites
const int TILE_RED = 0;
const int TILE_GREEN = 1;
const int TILE_BLUE = 2;
const int TILE_CENTER = 3;
const int TILE_TOP = 4;
const int TILE_TOPRIGHT = 5;
const int TILE_RIGHT = 6;
const int TILE_BOTTOMRIGHT = 7;
const int TILE_BOTTOM = 8;
const int TILE_BOTTOMLEFT = 9;
const int TILE_LEFT = 10;
const int TILE_TOPLEFT = 11;

class RenderWindow;

class Tile : public Entity{
public:
	Tile(float x, float y, SDL_Texture* p_tex , int tileType);
	void render(SDL_Rect& camera, RenderWindow& p_renderwindow);
	int getType();
	static bool setTiles(Tile* tiles[], SDL_Texture* p_tileTex);
	//get collison box
	SDL_Rect getBox();
	bool touchesWall(SDL_Rect box, Tile* tiles[], RenderWindow& p_renderwindow);
private:
	SDL_Rect box;
	int type;
	static SDL_Rect gTileClips[TOTAL_TILE_SPRITES];
};

