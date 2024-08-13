#pragma once
#include "Entity.h"
#include "Renderwindow.h"
#include "Map.h"
#include "Tile.h"
#include "Entity.h"
#include "Player.h"
#include "Monster.h"
#include "MainMenu.h"

using namespace std;

class MainGame {
public:
	MainGame(RenderWindow& renderwindow);
	bool init();
	void loadMedia();
	void loadPlayer();
	void loadMonster();
	void createMapLists();
	void loadMap();
	void updateMap();
	void loadMenu();
	void setTile();
	void loadScore();
	void updateBestScore();
	void updatePlayer();
	void updateMonster();
	void updateSpike();
	void updateGame();
	void renderMenu();
	void resetGame();
	void loadMenuMusic();
	void loadGameMusic();
	void handleGameEvent(SDL_Event& event);
	bool getIsRunning();
	vector<MainMenu> getMenus();

private:
	RenderWindow& p_renderwindow;
	bool isRunning = true;
	const int tong_map = TOTAL_MAP - 1;

	//cac texture
	SDL_Texture* playerTex = NULL;
	SDL_Texture* monsterTex = NULL;
	SDL_Texture* tileTex = NULL;
	SDL_Texture* spikeTex = NULL;
	SDL_Texture* buttonTex = NULL;
	SDL_Texture* backgroundTex = NULL;

	SDL_Rect tileClips[TOTAL_TILE_SPRITES];
	SDL_Rect spike[1];

	//camera
	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	float velCam = 1.5;

	//best score
	stringstream scoreText;
	stringstream bestscoreText;
	int score = 0;
	int bestscore = 0;

	//cac vector chua cac thuc the
	vector<Path> lists; //chua cac map
	vector<Map> maps; //chua cac map
	vector<Player> players;
	vector<Monster*> monsters;
	vector<MainMenu> menus;

	//sound
	Mix_Music* menuMusic = NULL;
	Mix_Music* gameMusic = NULL;
};
