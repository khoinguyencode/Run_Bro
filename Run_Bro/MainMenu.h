#pragma once
#include "RenderWindow.h"
#include "Time.h"
#include "Player.h"


using namespace std;

class MainMenu {
public:
	MainMenu(SDL_Texture* p_buttonTex, SDL_Texture* p_mainMenuBGTex, SDL_Texture* p_restartBGTex);
	void handleEvent(SDL_Event& event, bool& p_gameRunning, Player& p_player);
	void renderMainMenu();
	void renderRestartMenu();
private:
	const int BUTTON_WIDTH = 100;
	const int BUTTON_HEIGHT = 50;
	static const int TOTAL_BUTTONS = 3;
	SDL_Rect playButtonClips[TOTAL_BUTTONS];
	SDL_Rect exitButtonClips[TOTAL_BUTTONS];
	SDL_Rect restartButtonClips[TOTAL_BUTTONS];
};