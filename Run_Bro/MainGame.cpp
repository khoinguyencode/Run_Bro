#include "MainGame.h"
#include <iostream>
using namespace std;

MainGame::MainGame(RenderWindow& renderwindow)
	:p_renderwindow(renderwindow)
{
	setTile();
}

bool MainGame::init() {
	if (SDL_Init(SDL_INIT_VIDEO) > 0) {
		cout << "SDL Init failed: " << SDL_GetError << endl;
		return false;
	}
	if (!IMG_Init(IMG_INIT_PNG)) {
		cout << "IMG Init failed: " << SDL_GetError << endl;
		return false;
	}
	p_renderwindow = RenderWindow("Game", 100, 100);
	return true;
}

void MainGame::loadMedia() {
	p_renderwindow.loadTexture("res/gfx/DarkSamuraiX.png");
	p_renderwindow.loadTexture("res/gfx/DungeonTileSet.png");
}

void MainGame::loadPlayer() {
	Player samurai(100, 500, playerTex);
	players.push_back(samurai);
}

void MainGame::createMapLists() {
	lists.push_back("res/gfx/dungeon0.map");
	lists.push_back("res/gfx/dungeon1.map");
	lists.push_back("res/gfx/dungeon2.map");
	lists.push_back("res/gfx/dungeon3.map");
	lists.push_back("res/gfx/dungeon4.map");
	lists.push_back("res/gfx/dungeon5.map");
	lists.push_back("res/gfx/dungeon6.map");
	lists.push_back("res/gfx/dungeon7.map");
	lists.push_back("res/gfx/dungeon8.map");
	lists.push_back("res/gfx/dungeon9.map");
	lists.push_back("res/gfx/dungeon10.map");
	lists.push_back("res/gfx/dungeon11.map");
}

void MainGame::loadMap() {
	//render truoc 3 map
	for (int i = 0; i < 3; i++) {
		//chon ngau nhien 1 map
		int random = rand() % tong_map;
		if (i == 0) random = tong_map;
		if (random < lists.size()) {
			Map map(i * LEVEL_WIDTH, 0, lists[random], tileTex);
			maps.push_back(map);
		}
	}
}


void MainGame::updateMap() {
	//check xem map dau tien ra khoi man hinh chua
	if (maps[0].getX() - camera.x <= -LEVEL_WIDTH) {
		int random = rand() % tong_map;
		maps[0].setTilesType(lists[random]);

		//dat vi tri x cua map dau tien sao cho no nam ngay sau map cuối trong lists
		maps[0].setMap(maps[maps.size() - 1]);

		Map map = maps[0];
		//xoa map dau tien roi day map moi vao
		maps.erase(maps.begin());
		maps.push_back(map);
	}

	//render map
	for (int i = 0; i < maps.size(); i++) {
		maps[i].render(tileClips, camera, p_renderwindow);
	}
}
void MainGame::setTile() {
	int n = 0, m = 0;
	for (int i = 0; i < TOTAL_TILE_SPRITES; i++) {
		tileClips[i].x = n;
		tileClips[i].y = m;
		tileClips[i].w = TILE_WIDTH;
		tileClips[i].h = TILE_HEIGHT;
		n += TILE_WIDTH;
		//xuong dong
		if (n > 16 * TILE_WIDTH) {
			n = 0;
			m += TILE_HEIGHT;
		}
	}
}
void MainGame::updatePlayer() {
	players[0].update(p_renderwindow, maps);
	players[0].setCamera(camera, velCam);
	players[0].render(p_renderwindow, camera);
}
void updateGame();
void resetGame();

void MainGame::handleGameEvent(SDL_Event& event) {
	if(event.type == SDL_QUIT) isRunning = false;
}
bool isRunning();

bool MainGame::getIsRunning() {
	return isRunning;
}