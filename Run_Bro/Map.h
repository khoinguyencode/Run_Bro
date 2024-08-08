#pragma once
#include "Tile.h"
#include "SDL.h"
#include "vector"
#include "Renderwindow.h"
using namespace std;

const int TOTAL_MAP = 12;

class Tile;
class RenderWindow;

class Map {
public:
	Map(float p_x, float p_y, const char* p_filePath, SDL_Texture* p_tileTex);
	void render(SDL_Rect p_tileClips[], SDL_Rect& p_camera, RenderWindow& p_renderwindow);
	//void setX(float p_x);
	//void setLevel(Map& p_level);

	//reset lai game
	//void setTilesType(const char* p_filePath);
	vector<Tile*> getTiles();
	float getX();
	float getY();
private:
	float x, y;
	vector<Tile*> tiles; //vector chua con tro toi cac doi tuong Tile
};
