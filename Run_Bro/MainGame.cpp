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
	if (TTF_Init() == -1) {
		cout << "TTF_Init HAS FAILED. SDL_ERROR: " << TTF_GetError() << endl;
		return false;
	}
	return true;
}

void MainGame::loadMedia() {
	playerTex = p_renderwindow.loadTexture("res/gfx/test3.png");
	tileTex = p_renderwindow.loadTexture("res/gfx/DungeonTileSet.png");
	spikeTex = p_renderwindow.loadTexture("res/gfx/spiked.png");
	p_renderwindow.openFont("res/PixelFont.ttf");
}

void MainGame::loadPlayer() {
	Player samurai(500, 500, playerTex);
	players.push_back(samurai);
}

void MainGame::createMapLists() {
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
	lists.push_back("res/gfx/dungeon0.map");
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

void MainGame::loadScore() {
	// cap nhat diem neu vi tri cua nguoi choi lon hon diem hien tai
	if (score < players[0].getX() / TILE_WIDTH) score = players[0].getX() / TILE_WIDTH;

	//xoa noi dung hien tai trong scoreText va cap nhat diem moi
	scoreText.str("");
	scoreText << "Score: " << score << "m";

	ifstream readFile;
	readFile.open("res/bestscore.txt");
	if (readFile.fail()) updateBestScore();
	readFile >> bestscore;
	bestscoreText.str("");
	bestscoreText << "Best Score: " << bestscore << "m";

	SDL_Texture* scoreTex = p_renderwindow.loadText(scoreText.str().c_str(), { 255,255,255,255 });
	SDL_Texture* bestscoreTex = p_renderwindow.loadText(bestscoreText.str().c_str(), { 255, 0, 0, 255 });
	Entity cur_score(1120, 30, scoreTex);
	Entity best_score(1120, 0, bestscoreTex);
	p_renderwindow.renderText(cur_score);
	p_renderwindow.renderText(best_score);
}

void MainGame::updateBestScore() {
	ofstream outFile;
	outFile.open("res/bestscore.txt");
	outFile.clear();
	outFile << bestscore;
	outFile.close();
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
	spike[0].x = 0;
	spike[0].y = 0;
	spike[0].w = 64;
	spike[0].h = 1728;
}

void MainGame::updatePlayer() {
	players[0].update(p_renderwindow, maps, camera);
	players[0].setCamera(camera, velCam);
	players[0].render(p_renderwindow, camera);
}

void MainGame::updateSpike() {
	p_renderwindow.renderSpike(spikeTex, camera.x, 0, spike[0], camera, 0, NULL, SDL_FLIP_NONE);
}

void MainGame::updateGame() {
	p_renderwindow.clear();
	updateMap();
	updatePlayer();
	updateSpike();
	loadScore();
	if (players[0].getDead()) {
		if (score > bestscore) bestscore = score;
		updateBestScore();
	}
	p_renderwindow.display();
}

void MainGame::resetGame() {
	players[0].resetPlayer();
	camera.x = 0;
	camera.y = 0;
	velCam = 1.5;

	for (int i = 0; i < maps.size(); i++) {
		int random = rand() % (tong_map);
		if (i == 0) {
			random = tong_map;
			maps[i].setX(0);
		}
		else maps[i].setMap(maps[i - 1]);
		maps[i].setTilesType(lists[random]);
	}
}

void MainGame::handleGameEvent(SDL_Event& event) {
	if(event.type == SDL_QUIT) isRunning = false;
	players[0].handleEvent(event);
}

bool MainGame::getIsRunning() {
	return isRunning;
}
