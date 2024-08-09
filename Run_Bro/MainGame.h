#pragma once
#include "Entity.h"
#include "Renderwindow.h"
#include "Map.h"
#include "Tile.h"
#include "Entity.h"
#include "Player.h"


class MainGame {
public:
	MainGame(RenderWindow& renderwindow);
	bool init();
	void loadMedia();
	void loadPlayer();
	void createMapLists();
	void loadMap();
	void updateMap();
	void setTile();
	void updatePlayer();
	void updateGame();
	void resetGame();
	void handleGameEvent(SDL_Event& event);
	bool getIsRunning();


private:
	RenderWindow& p_renderwindow;
	bool isRunning = true;
	int tong_map = TOTAL_MAP - 1;
	//cac texture
	SDL_Texture* playerTex = NULL;
	SDL_Texture* tileTex = NULL;

	SDL_Rect tileClips[TOTAL_TILE_SPRITES];

	//camera
	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	float velCam = 1.3;

	vector<const char*> lists; //chua cac map
	vector<Map> maps; //chua cac map
	vector<Player> players;
};