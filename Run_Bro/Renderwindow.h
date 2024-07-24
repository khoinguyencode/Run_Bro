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

    //ve cac thuc the
    void render(Entity& p_entity);

    SDL_Renderer* getRenderer() const;

    //ve nguoi choi, quai vat len man hinh
    void renderAnimation(Entity& p_entity, SDL_Rect& p_clip, SDL_Rect& p_camera, double p_angle, SDL_Point* p_center, SDL_RendererFlip p_flip);
    void display();
    static bool checkCollision(SDL_Rect a, SDL_Rect b);
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};
