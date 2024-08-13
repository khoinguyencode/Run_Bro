#include "MainMenu.h"

MainMenu::MainMenu(SDL_Texture* buttonTex, SDL_Texture* mainMenuTex, SDL_Texture* restartTex) {
	for (int i = 0; i < TOTAL_BUTTONS; i++) {
		playButton[i].x = i * BUTTON_WIDTH;
		playButton[i].y = 0;
		playButton[i].w = BUTTON_WIDTH;
		playButton[i].h = BUTTON_HEIGHT;

		exitButton[i].x = i * BUTTON_WIDTH;
		exitButton[i].y = BUTTON_HEIGHT;
		exitButton[i].w = BUTTON_WIDTH;
		exitButton[i].h = BUTTON_HEIGHT;

		restartButton[i].x = i * BUTTON_WIDTH;
		restartButton[i].y = BUTTON_HEIGHT * 2;
		restartButton[i].w = BUTTON_WIDTH;
		restartButton[i].h = BUTTON_HEIGHT;
	}
	this->buttonTex = buttonTex;
	this->mainMenuTex = mainMenuTex;
	this->restartTex = restartTex;
}

void MainMenu::handleEvent(SDL_Event& p_event, bool& p_gameRunning, Player& p_player){
	switch (p_event.type) {
	//nhan chuot
	case SDL_MOUSEBUTTONDOWN:
		if (p_event.button.button == SDL_BUTTON_LEFT) {
			if (menu) {
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
		if (menu) {
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

bool MainMenu::getReset() const{
	return reset;
}

void MainMenu::set_reset(bool p_reset) {
	reset = p_reset;
}

bool MainMenu::checkMouseAt(int p_x, int p_y) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x >= p_x && y >= p_y && x <= p_x + BUTTON_WIDTH && y <= p_y + BUTTON_HEIGHT) return true;
	return false;
}

void MainMenu::renderMainMenu(RenderWindow& p_renderwindow) {
	if (menu) {
		p_renderwindow.renderTexture(mainMenuTex, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		if (selected[0]) p_renderwindow.renderTexture(buttonTex, button1.x, button1.y, 0, 0, &playButton[1]);
		else if (!pressed[0]) p_renderwindow.renderTexture(buttonTex, button1.x, button1.y, 0, 0, &playButton[0]);
		else p_renderwindow.renderTexture(buttonTex, button1.x, button1.y, 0, 0, &playButton[2]);

		if (selected[1]) p_renderwindow.renderTexture(buttonTex, button2.x, button2.y, 0, 0, &exitButton[1]);
		else if (!pressed[1]) p_renderwindow.renderTexture(buttonTex, button2.x, button2.y, 0, 0, &exitButton[0]);
		else p_renderwindow.renderTexture(buttonTex, button2.x, button2.y, 0, 0, &exitButton[2]);
	}
}

void MainMenu::renderRestartMenu(RenderWindow& p_renderwindow) {
	if (selected[2]) p_renderwindow.renderTexture(buttonTex, button1.x, button1.y, 0, 0, &restartButton[1]);
	else if (!pressed[2]) p_renderwindow.renderTexture(buttonTex, button1.x, button1.y, 0, 0, &restartButton[0]);
	else p_renderwindow.renderTexture(buttonTex, button1.x, button1.y, 0, 0, &restartButton[2]);

	if (selected[3]) p_renderwindow.renderTexture(buttonTex, button2.x, button2.y, 0, 0, &exitButton[1]);
	else if (!pressed[3]) p_renderwindow.renderTexture(buttonTex, button2.x, button2.y, 0, 0, &exitButton[0]);
	else p_renderwindow.renderTexture(buttonTex, button2.x, button2.y, 0, 0, &exitButton[2]);
}

