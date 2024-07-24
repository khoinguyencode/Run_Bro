#pragma once
#include "Entity.h"

const float GRAVITY = 0.3;
const float MAX_GRAVITY = 15;

class RenderWindow {
public:
    RenderWindow(const char* p_title, int p_w, int p_h);
    SDL_Texture* loadTexture(const char* p_filePath);
    void cleanUp();
    void clear();
    void render(Entity& p_entity);
    void renderAnimation(Entity& p_entity, double angel = 0.0, SDL_Point* p_point = NULL, SDL_RendererFlip p_flip = SDL_FLIP_NONE);
    void display();
    static bool checkCollision(SDL_Rect a, SDL_Rect b);
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};
