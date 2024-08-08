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

    Player player(0, 600, playerTex);

    // Load the map
    vector<const char*> maps;
    vector<Map> levels;


    maps.push_back("res/gfx/dungeon0.map");
    maps.push_back("res/gfx/dungeon1.map");
    maps.push_back("res/gfx/dungeon2.map");
    maps.push_back("res/gfx/dungeon3.map");
    maps.push_back("res/gfx/dungeon4.map");
    maps.push_back("res/gfx/dungeon5.map");
    maps.push_back("res/gfx/dungeon6.map");
    maps.push_back("res/gfx/dungeon7.map");
    maps.push_back("res/gfx/dungeon8.map");
    maps.push_back("res/gfx/dungeon9.map");
    maps.push_back("res/gfx/dungeon10.map");
    maps.push_back("res/gfx/dungeon11.map");

    //khong tinh map 0
    int tong_map = TOTAL_MAP - 1;

    //render 3 map dau
    for (int i = 0; i < 3; i++) {
        //lay ngau nhien 1 map
        int random = rand() % tong_map;
        if (i == 0) random = tong_map;
        Map map(i * LEVEL_WIDTH, 0, maps[random], tileTex);
        levels.push_back(map);
    }
    
    Map gameMap(0, 0, "res/gfx/dungeon0.map", tileTex);

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
    float velCam = 1.5;
    while (gameRunning) {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                gameRunning = false;
            else
                player.handleEvent(event);
        }
        player.update(window, gameMap);
        player.setCamera(camera, velCam);
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
