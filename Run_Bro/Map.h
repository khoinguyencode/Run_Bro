#pragma once
#include "Tile.h"
#include "SDL.h"
#include "vector"
#include "Renderwindow.h"
using namespace std;

const int TOTAL_MAP = 12;

class Tile;
class RenderWindow;

struct Path {
	const char* path;
	vector<int> monsterPos;

	//khoi tao lists
	Path(vector<int> monsterPos, const char* p_path) {
		path = p_path;
		this->monsterPos = monsterPos;
	}
};

class Map {
public:
	Map(float p_x, float p_y, const char* p_filePath, SDL_Texture* p_tileTex);
	void render(SDL_Rect p_tileClips[], SDL_Rect& p_camera, RenderWindow& p_renderwindow);
	void setX(float p_x); //dam bao vi tri cac o trong map cung dich chuyen theo vi tri moi cua map
	void setMap(Map& p_map); //dat vi tri map hien tai ngay canh ben phai p_map 
	
	void setTilesType(const char* p_filePath);
	vector<Tile*> getTiles();
	float getX();
	float getY();
	vector<int> getMonsterPos();
private:
	float x, y;
	vector<Tile*> tiles; //vector chua con tro toi cac doi tuong Tile
	vector<int> monsterPos;
};
