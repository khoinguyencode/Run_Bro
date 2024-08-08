#include "SDL.h"
#include <iostream>
#include <vector>
#include <SDL_image.h>
#include "Renderwindow.h"
#include "Entity.h"
#include "Player.h"
#include "Tile.h"
#include "Map.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        cout << "SDL_init failed. SDL_ERROR: " << SDL_GetError() << endl;

    if (!(IMG_Init(IMG_INIT_PNG)))
        cout << "Img_init failed. SDL_ERROR: " << SDL_GetError() << endl;

    RenderWindow window("Game V1.0", SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_Texture* playerTex = window.loadTexture("res/gfx/DarkSamuraiX.png");
    SDL_Texture* tileTex = window.loadTexture("res/gfx/fake.png");

    Player player(0, 0, playerTex);

    // Load the map
    Map gameMap(0, 0, "res/gfx/dungeon11.map", tileTex);

    SDL_Rect tileClips[TOTAL_TILE_SPRITES];
    int n = 0, m = 0;
    for (int i = 0; i < TOTAL_TILE_SPRITES; i++) {
        tileClips[i].x = n;
        tileClips[i].y = m;
        tileClips[i].w = TILE_WIDTH;
        tileClips[i].h = TILE_HEIGHT;
        n += TILE_WIDTH;
        //xuong dong
        if (n > 16 * TILE_WIDTH) {
            n = 0;
            m += TILE_HEIGHT;
        }
    }

    bool gameRunning = true;
    SDL_Event event;

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    while (gameRunning) {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                gameRunning = false;
            else
                player.handleEvent(event);
        }
        player.update(window, gameMap);
        player.setCamera(camera);
        window.clear();

        // Render the map
        gameMap.render(tileClips, camera, window);

        // Render the player
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
