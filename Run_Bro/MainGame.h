#pragma once
#include "Entity.h"
#include "Renderwindow.h"
#include "Map.h"
#include "Tile.h"
#include "Entity.h"
#include "Player.h"

using namespace std;

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
	void loadScore();
	void updateBestScore();
	void updatePlayer();
	void updateSpike();
	void updateGame();
	void resetGame();
	void handleGameEvent(SDL_Event& event);
	bool getIsRunning();


private:
	RenderWindow& p_renderwindow;
	bool isRunning = true;
	const int tong_map = TOTAL_MAP - 1;
	//cac texture
	SDL_Texture* playerTex = NULL;
	SDL_Texture* tileTex = NULL;
	SDL_Texture* spikeTex = NULL;

	SDL_Rect tileClips[TOTAL_TILE_SPRITES];
	SDL_Rect spike[1];

	//camera
	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	float velCam = 1.5;

	stringstream scoreText;
	stringstream bestscoreText;
	int score = 0;
	int bestscore = 0;

	vector<const char*> lists; //chua cac map
	vector<Map> maps; //chua cac map
	vector<Player> players;
};