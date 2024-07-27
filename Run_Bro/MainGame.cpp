#include "MainGame.h"

#include <iostream>
using namespace std;

bool MainGame::init(RenderWindow& p_renderwindow) {
	if (SDL_Init(SDL_INIT_VIDEO) > 0) {
		cout << "SDL Init failed: " << SDL_GetError << endl;
		return false;
	}
	if (IMG_Init(IMG_INIT_PNG)) {
		cout << "IMG Init failed: " << SDL_GetError << endl;
		return false;
	}
	p_renderwindow = RenderWindow("Game", 100, 100);
	return true;
}

void MainGame::loadMedia(RenderWindow& p_renderwindow) {
	p_renderwindow.loadTexture("res/gfx/DarkSamuraiX.png");
	p_renderwindow.loadTexture("res/gfx/ground_grass_1.png");
}

