#pragma once
#include "Entity.h"
#include "Tile.h"
//kich co screen
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 720;

//kich co level
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

class Tile;

class RenderWindow {
public:
    RenderWindow(const char* p_title, int p_w, int p_h);
    SDL_Texture* loadTexture(const char* p_filePath);
    void cleanUp();
    void clear();

    //ve cac thuc the
    void render(Entity& p_entity);

    SDL_Renderer* getRenderer() const;

    //ve cac animation len man hinh
    void renderAnimation(Entity& p_entity, SDL_Rect& p_clip, SDL_Rect& p_camera, double p_angle, SDL_Point* p_center, SDL_RendererFlip p_flip);

    //ve tile
    void renderTile(Entity& p_entity, SDL_Rect& p_clip, SDL_Rect& camera);

    void display();
    static bool checkCollision(SDL_Rect a, SDL_Rect b);
    bool touchesWall(SDL_Rect box, Tile* tiles[]);
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};
