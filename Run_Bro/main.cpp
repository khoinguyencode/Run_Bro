#include "SDL.h"
#include <iostream>
#include <vector>
#include <SDL_image.h>
#include "Renderwindow.h"
#include "Entity.h"
#include "Player.h"
#include "Tile.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        cout << "SDL_init failed. SDL_ERROR: " << SDL_GetError() << endl;

    if (!(IMG_Init(IMG_INIT_PNG)))
        cout << "Img_init failed. SDL_ERROR: " << SDL_GetError() << endl;

    RenderWindow window("Game V1.0", SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_Texture* tex = window.loadTexture("res/gfx/DarkSamuraiX.png");
    SDL_Texture* texTile = window.loadTexture("tiles.png");

    Player player(100, 0, tex);

    bool gameRunning = true;
    SDL_Event event;

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    Tile* tileSet[TOTAL_TILES];

    if (!Tile::setTiles(tileSet, texTile)) {
        cout << "Failed to load tile set!" << endl;
        return -1;
    }

    while (gameRunning) {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                gameRunning = false;
            else
                player.handleEvent(event);
        }
        player.update(window, tileSet);
        player.setCamera(camera);
        window.clear();
        for (int i = 0; i < TOTAL_TILES; ++i)
        {
            tileSet[i]->render(camera, window);
        }

        player.render(window, camera);
        window.display();
        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    window.cleanUp();
    SDL_Quit();

    return 0;
}
