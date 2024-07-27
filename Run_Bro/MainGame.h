#pragma once
#include "Entity.h"
#include "Renderwindow.h"

class MainGame {
public:
	bool init(RenderWindow& p_renderwindow);
	void loadMedia(RenderWindow& p_renderwindow);
private:
	bool gameRunning = true;
};