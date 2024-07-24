#include "SDL.h"
#include <iostream>
#include <vector>
#include <SDL_image.h>
#include "Renderwindow.h"
#include "Entity.h"
#include "Player.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        cout << "SDL_init failed. SDL_ERROR: " << SDL_GetError() << endl;

    if (!(IMG_Init(IMG_INIT_PNG)))
        cout << "Img_init failed. SDL_ERROR: " << SDL_GetError() << endl;

    RenderWindow window("Game V1.0", 1280, 720);

    SDL_Rect camera = { 0, 0, 1280, 720 };
    SDL_Texture* tex = window.loadTexture("res/gfx/DarkSamurai.png");

    Player player(100, 355, tex);

    SDL_Rect wall;
    wall.x = 500;
    wall.y = 200;
    wall.w = 200;
    wall.h = 700;

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
        player.update(window, wall);

        window.clear();

        SDL_SetRenderDrawColor(window.getRenderer(), 255, 0, 0, 255); // Đặt màu đỏ
        SDL_RenderFillRect(window.getRenderer(), &wall);

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
