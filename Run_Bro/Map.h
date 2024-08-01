#pragma once
#include "Tile.h"
#include "SDL.h"
#include "vector"
using namespace std;

class Tile;

class Map {
public:
	Map(const char* p_filePath, SDL_Texture* p_tileTex);
	void render(SDL_Rect p_TileClips[], SDL_Rect& p_camera);

	vector<Tile*> getTiles();
	float getX();
	float getY();
private:
	float x, y;
	vector<Tile*> tiles;
};