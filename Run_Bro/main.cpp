#include "SDL.h"
#include <iostream>
#include <vector>
#include <SDL_image.h>
#include "Renderwindow.h"
#include "Entity.h"
#include "Player.h"
#include "Tile.h"
#include "Map.h"
#include "MainGame.h"

using namespace std;

int main(int argc, char* argv[]) {
    RenderWindow window("Game", SCREEN_WIDTH, SCREEN_HEIGHT);
    MainGame game(window);
    srand(time(NULL));
    if (game.init()) {
        game.loadMedia();
        game.createMapLists();
        game.loadMap();
        game.loadPlayer();
        game.loadMonster();
        game.loadMenu();
        while (game.getIsRunning()) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                game.handleGameEvent(event);
            }
            if (game.getMenus()[0].getMenu()) {
                game.renderMenu();
                game.loadMenuMusic();
            }
            else if (game.getMenus()[0].getPaused()) {
                cout << "Da bam\n";
                game.pauseMusic();
            }
            else {
                game.updateGame();
                game.loadGameMusic();
            }
        }
    }
    window.cleanUp();
    return 0;
}
