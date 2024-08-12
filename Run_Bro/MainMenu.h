#pragma once
#include "RenderWindow.h"
#include "Time.h"
#include "Player.h"


using namespace std;

class MainMenu {
public:
	MainMenu(SDL_Texture* p_buttonTex, SDL_Texture* p_mainMenuBGTex, SDL_Texture* p_restartBGTex);
	void handleEvent(SDL_Event& event, bool& p_gameRunning, Player& p_player);
	void renderMainMenu(RenderWindow& p_renderwindow);
	void renderRestartMenu(RenderWindow& p_renderwindow);
	bool checkMouseAt(int x, int y); //kiem tra chuot tai 1 vung
	bool getMenu();
	bool getPaused();
	bool getReset() const;
	void set_reset(bool p_reset);
private:
	const int BUTTON_WIDTH = 192;
	const int BUTTON_HEIGHT = 96;
	static const int TOTAL_BUTTONS = 3; //3 loai nut: choi, thoat, restart
	SDL_Rect playButton[TOTAL_BUTTONS];
	SDL_Rect exitButton[TOTAL_BUTTONS];
	SDL_Rect restartButton[TOTAL_BUTTONS];

	bool menu = true, reset = false, paused = false, restart = false;
	bool selected[4] = { false }; //check chon
	bool pressed[4] = { false }; //check nhan

	//vi tri cac nut
	SDL_Point button1 = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 + 16};
	SDL_Point button2 = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 + BUTTON_HEIGHT + 48 };

	SDL_Texture* buttonTex = NULL;
	SDL_Texture* mainMenuTex = NULL;
	SDL_Texture* restartTex = NULL;
};