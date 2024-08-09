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
    if (game.init()) {
        game.loadMedia();
        game.loadPlayer();
        game.createMapLists();
        game.loadMap();
        SDL_Event event;
        while (game.getIsRunning()) {
            while (SDL_PollEvent(&event)) {
                game.handleGameEvent(event);
            }
        }
    }
    return 0;
}
