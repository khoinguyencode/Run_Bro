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

    SDL_Texture* idleTex = window.loadTexture("Idle.png");
    SDL_Texture* runTex = window.loadTexture("Run.png");
    SDL_Texture* jumpTex = window.loadTexture("Jump.png");
    SDL_Texture* fallTex = window.loadTexture("Fall.png");
    SDL_Texture* attackTex = window.loadTexture("Attack1.png");
    SDL_Texture* deathTex = window.loadTexture("Death.png");
    SDL_Texture* grassTex = window.loadTexture("ground_grass_1.png");

    Player player(100, 300, idleTex);
    player.setTextures(idleTex, runTex, jumpTex, fallTex, attackTex, deathTex);

    Entity e(100, 450, grassTex);

    bool gameRunning = true;
    SDL_Event event;

    // FPS and frame time calculation
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

        player.update();

        window.clear();
        window.renderAnimation(player, 0.0, NULL, player.getflipType());
        window.render(e);
        window.display();

        // Frame rate capping
        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    window.cleanUp();
    SDL_Quit();

    return 0;
}
