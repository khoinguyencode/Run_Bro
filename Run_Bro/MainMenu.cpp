#include "MainMenu.h"

MainMenu::MainMenu(SDL_Texture* buttonTex, SDL_Texture* mainMenuBGTex, SDL_Texture* retryBGTex) {
	for (int i = 0; i < TOTAL_BUTTONS; i++) {
		playButtonClips[i].x = i * BUTTON_WIDTH;
		playButtonClips[i].y = 0;
		playButtonClips[i].w = BUTTON_WIDTH;
		playButtonClips[i].h = BUTTON_HEIGHT;

		exitButtonClips[i].x = i * BUTTON_WIDTH;
		exitButtonClips[i].y = BUTTON_HEIGHT + 20;
		exitButtonClips[i].w = BUTTON_WIDTH;
		exitButtonClips[i].h = BUTTON_HEIGHT;

		restartButtonClips[i].x = i * BUTTON_WIDTH;
		restartButtonClips[i].y = BUTTON_HEIGHT * 2 + 20;
		restartButtonClips[i].w = BUTTON_WIDTH;
		restartButtonClips[i].h = BUTTON_HEIGHT;
	}
}

void MainMenu::handleEvent(SDL_Event& p_event, bool& p_gameRunning, Player& p_player){
	switch (p_event.type) {
	//nhan chuot
	case SDL_MOUSEBUTTONDOWN:
		break;
	//tha chuot ra
	case SDL_MOUSEBUTTONUP:
	//di chuyen chuot
	case SDL_MOUSEMOTION:
		break;
	case SDL_KEYDOWN:
	default:
		break;
	}
}

void MainMenu::renderMainMenu(){}
void MainMenu::renderRestartMenu(){}