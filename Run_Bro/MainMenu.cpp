#include "MainMenu.h"

MainMenu::MainMenu(SDL_Texture* buttonTex, SDL_Texture* mainMenuBGTex, SDL_Texture* retryBGTex) {
	for (int i = 0; i < TOTAL_BUTTONS; i++) {
		playButtonClips[i].x = i * BUTTON_WIDTH;
		playButtonClips[i].y = 0;
		playButtonClips[i].w = BUTTON_WIDTH;
		playButtonClips[i].h = BUTTON_HEIGHT;

		exitButtonClips[i].x = i * BUTTON_WIDTH;
		exitButtonClips[i].y = BUTTON_HEIGHT;
		exitButtonClips[i].w = BUTTON_WIDTH;
		exitButtonClips[i].h = BUTTON_HEIGHT;

		restartButtonClips[i].x = i * BUTTON_WIDTH;
		restartButtonClips[i].y = BUTTON_HEIGHT;
		restartButtonClips[i].w = BUTTON_WIDTH;
		restartButtonClips[i].h = BUTTON_HEIGHT;
	}
}

void MainMenu::handleEvent(SDL_Event& p_event, bool& p_gameRunning, Player& p_player){
	switch (p_event.type) {
	//nhan chuot
	case SDL_MOUSEBUTTONDOWN:
		if (p_event.button.button == SDL_BUTTON_LEFT) {
			if (getMenu()) {
				if (checkMouseAt(button1.x, button1.y)) {
					pressed[0] = true; //bam Play trong menu
					menu = false;
				}
				if (checkMouseAt(button2.x, button2.y)) {
					pressed[1] = true; //bam exit
					p_gameRunning = false;
				}
			}
			if (p_player.getDead()) {
				if (checkMouseAt(button1.x, button1.y)) {
					pressed[2] = true; //restart
					reset = true;
				}
				if (checkMouseAt(button2.x, button2.y)) {
					pressed[3] = true; //exit
					p_gameRunning = false;
				}
			}
		}
		break;
	//tha chuot ra
	case SDL_MOUSEBUTTONUP:
		for (int i = 0; i <= 3; i++) {
			pressed[i] = false;
		}
		break;
	//di chuyen chuot
	case SDL_MOUSEMOTION:
		if (getMenu()) {
			//con tro chuot di chuyen qua nut Play
			if (checkMouseAt(button1.x, button1.y) && !pressed[0]) {
				selected[0] = true; 
			}
			else selected[0] = false;
			
			//exit
			if (checkMouseAt(button2.x, button2.y) && !pressed[1]) {
				selected[1] = true;
			}
			else selected[1] = false;
		}
		if (p_player.getDead()) {
			//restart
			if (checkMouseAt(button1.x, button1.y) && !pressed[2]) {
				selected[2] = true;
			}
			else selected[2] = false;

			//exit
			if (checkMouseAt(button2.x, button2.y) && !pressed[3]) {
				selected[3] = true;
			}
			else selected[3] = false;
		}
		break;
	case SDL_KEYDOWN:
		if (p_event.key.repeat == 0) {
			switch (p_event.key.keysym.sym) {
			case SDLK_ESCAPE:
				if (!paused) paused = true;
				else paused = false;
			}
		}
	default:
		break;
	}
}

bool MainMenu::getMenu() {
	return menu;
}

bool MainMenu::getPaused() {
	return paused;
}

bool MainMenu::getReset() {
	return reset;
}

bool MainMenu::checkMouseAt(int p_x, int p_y) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x >= p_x && y >= p_y && x <= p_x + BUTTON_WIDTH && y <= p_y + BUTTON_HEIGHT) return true;
	return false;
}

void MainMenu::renderMainMenu(RenderWindow& p_renderwindow) {
	if (menu) {
		p_renderwindow.renderText(*this, 0, 0, 1280, 720);
		p_renderwindow.renderText(*this, button1.x, button1.y);
	}
}
void MainMenu::renderRestartMenu(){}