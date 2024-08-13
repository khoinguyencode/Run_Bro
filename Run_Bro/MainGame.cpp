#include "MainGame.h"
#include <iostream>
using namespace std;

MainGame::MainGame(RenderWindow& renderwindow)
	:p_renderwindow(renderwindow)
{
	setTile();
}

bool MainGame::init() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		cout << "SDL Init failed: " << SDL_GetError << endl;
		return false;
	}
	if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
		cout << "IMG_Init HAS FAILED. SDL_ERROR: " << IMG_GetError << endl;
		return false;
	}
	if (TTF_Init() == -1) {
		cout << "TTF_Init HAS FAILED. SDL_ERROR: " << TTF_GetError << endl;
		return false;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}
	return true;
}

void MainGame::loadMedia() {
	playerTex = p_renderwindow.loadTexture("res/gfx/test3.png");
	monsterTex = p_renderwindow.loadTexture("res/gfx/testmonster.png");
	tileTex = p_renderwindow.loadTexture("res/gfx/DungeonTileSet.png");
	spikeTex = p_renderwindow.loadTexture("res/gfx/spiked.png");
	p_renderwindow.openFont("res/PixelFont.ttf");
	buttonTex = p_renderwindow.loadTexture("res/gfx/Button.png");
	backgroundTex = p_renderwindow.loadTexture("res/gfx/ds3.jpg");
	menuMusic = Mix_LoadMUS("res/music/inMenu.mp3");
	gameMusic = Mix_LoadMUS("res/music/inGame.mp3");
}

void MainGame::loadPlayer() {
	Player samurai(90, 700, playerTex);
	players.push_back(samurai);
}

void MainGame::loadMonster() {
	for (int i = 0; i < maps.size(); i++) {
		if (maps[i].getMonsterPos().size() > 0) {
			for (int j = 0; j < maps[i].getMonsterPos().size() - 1; j += 2) {
				Monster* monster = new Monster(maps[i].getMonsterPos()[j] * TILE_WIDTH + maps[i].getX(), maps[i].getMonsterPos()[j + 1] * TILE_WIDTH + maps[i].getY(), monsterTex);
				monsters.push_back(monster);
			}
		}
	}
}

void MainGame::createMapLists() {
	lists.push_back(Path({ (10, 6), (7, 7)}, "res/gfx/dungeon1.map"));
	lists.push_back(Path({(10, 10)}, "res/gfx/dungeon2.map"));
	lists.push_back(Path({ (9, 9), (17, 5)}, "res/gfx/dungeon3.map"));
	lists.push_back(Path({ 14, 11 ,15, 11}, "res/gfx/dungeon4.map"));
	lists.push_back(Path({ (9, 9), (16, 5)}, "res/gfx/dungeon5.map"));
	lists.push_back(Path({ (9, 9), (10, 9), (9, 9)}, "res/gfx/dungeon6.map"));
	lists.push_back(Path({ (15, 11), (15, 5), (12, 6)}, "res/gfx/dungeon7.map"));
	lists.push_back(Path({ (7, 12), (16, 11), (16, 11), (16, 11)}, "res/gfx/dungeon8.map"));
	lists.push_back(Path({ (11, 5), (15, 10)}, "res/gfx/dungeon9.map"));
	lists.push_back(Path({ (10, 3), (14, 11), (14, 11), (14, 11)}, "res/gfx/dungeon10.map"));
	lists.push_back(Path({ }, "res/gfx/dungeon11.map"));
	lists.push_back(Path({ (14, 11)}, "res/gfx/dungeon0.map"));
}

void MainGame::loadMap() {
	//render truoc 3 map
	for (int i = 0; i < 3; i++) {
		//chon ngau nhien 1 map
		int random = rand() % tong_map;
		if (i == 0) random = tong_map;
		if (random < lists.size()) {
			Map map(i * MAP_WIDTH, 0, lists[random].path, tileTex);
			map.setMonsterPos(lists[random].monsterPos);
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

void MainGame::loadMenu() {
	MainMenu gameMenu(buttonTex, backgroundTex, backgroundTex);
	menus.push_back(gameMenu);
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
	if (maps[0].getX() - camera.x <= -MAP_WIDTH) {
		int random = rand() % tong_map;
		maps[0].setTilesType(lists[random].path);

		//dat vi tri x cua map dau tien sao cho no nam ngay sau map cuối trong lists
		maps[0].setMap(maps[maps.size() - 1]);

		maps[0].setMonsterPos(lists[random].monsterPos);
		if (maps[0].getMonsterPos().size() > 0) {
			for (int j = 0; j < maps[0].getMonsterPos().size() - 1; j += 2) {
				Monster* monster = new Monster(maps[0].getMonsterPos()[j] * TILE_WIDTH + maps[0].getX(), maps[0].getMonsterPos()[j + 1] * TILE_WIDTH + maps[0].getY(), monsterTex);
				monsters.push_back(monster);
			}
		}

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

void MainGame::renderMenu() {
	p_renderwindow.clear();
	menus[0].renderMainMenu(p_renderwindow);
	p_renderwindow.display();
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
	players[0].update(p_renderwindow, maps, camera, monsters);
	players[0].setCamera(camera, velCam);
	players[0].render(p_renderwindow, camera);
}

void MainGame::updateMonster() {
	for (int i = 0; i < monsters.size(); i++) {
		if (monsters[i] != NULL) {
			if (monsters[i]->getDead()) {
				delete monsters[i];
				monsters[i] = NULL;
				monsters.erase(monsters.begin() + i);
			}
			else {
				monsters[i]->render(p_renderwindow, camera);
				monsters[i]->update(p_renderwindow, maps, camera, players[0]);
			}
		}
	}
}

void MainGame::updateSpike() {
	p_renderwindow.renderSpike(spikeTex, camera.x, 0, spike[0], camera, 0, NULL, SDL_FLIP_NONE);
}

void MainGame::updateGame() {
	p_renderwindow.clear();
	updateMap();
	updatePlayer();
	updateMonster();
	updateSpike();
	loadScore();
	if (players[0].getDead()) {
		menus[0].renderRestartMenu(p_renderwindow);
		if (score > bestscore) bestscore = score;
		updateBestScore();
	}
	if (menus[0].getReset()) resetGame();
	p_renderwindow.display();
}

void MainGame::resetGame() {
	players[0].resetPlayer();
	camera.x = 0;
	camera.y = 0;
	velCam = 1.5;

	//delete monster
	if (!maps.empty())
		for (int i = monsters.size() - 1; i >= 0; i--) {
			delete monsters[i];
			monsters[i] = NULL;
			monsters.erase(monsters.begin() + i);
		}

	for (int i = 0; i < maps.size(); i++) {
		int random = rand() % (tong_map);
		if (i == 0) {
			random = tong_map;
			maps[i].setX(0);
		}
		else maps[i].setMap(maps[i - 1]);
		maps[i].setTilesType(lists[random].path);
		maps[i].setMonsterPos(lists[random].monsterPos);
	}
	loadMonster();
	menus[0].set_reset(false);
	score = 0;
}

void MainGame::handleGameEvent(SDL_Event& event) {
	if (event.type == SDL_QUIT) isRunning = false;
	menus[0].handleEvent(event, isRunning, players[0]);
	if (!menus[0].getMenu() && !menus[0].getPaused()) players[0].handleEvent(event);
}

bool MainGame::getIsRunning() {
	return isRunning;
}

vector<MainMenu> MainGame::getMenus() {
	return menus;
}

void MainGame::loadMenuMusic() {
	//if (Mix_PlayingMusic() == 0 || Mix_PlayingMusic() && Mix_GetMusicType(NULL) != MUS_MP3) {
	//	Mix_HaltMusic();  // Dừng nhạc hiện tại
	//	Mix_PlayMusic(menuMusic, -1);  // Phát nhạc menu
	//}
}

void MainGame::loadGameMusic() {
	if (Mix_PlayingMusic() == 0 || Mix_PlayingMusic() && Mix_GetMusicType(NULL) != MUS_MP3) {
		Mix_HaltMusic();  // Dừng nhạc hiện tại
		Mix_PlayMusic(gameMusic, -1);  // Phát nhạc game
	}
}