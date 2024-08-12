#pragma once
#include "Entity.h"
#include "Tile.h"
#include "Map.h"
#include <vector>
#include <string>
#include "SDL_ttf.h"
#include <fstream>
#include <sstream>
using namespace std;
//kich co screen
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

//kich co map
const int MAP_WIDTH = 1344; //1 pixel width cua 1 tile(64) x so cot(24)
const int MAP_HEIGHT = 1024; //1 pixel height cua 1 tile(64) x so dong(16)

static TTF_Font* font = NULL;

class Tile;
class Map;

class RenderWindow {
public:
    RenderWindow(const char* p_title, int p_w, int p_h);
    SDL_Texture* loadTexture(const char* p_filePath);
    void cleanUp();
    void clear();

    SDL_Renderer* getRenderer() const;

    //ve cac animation len man hinh
    
    void renderAnimation(Entity& p_entity, SDL_Rect& p_clip, SDL_Rect& p_camera, double p_angle, SDL_Point* p_center, SDL_RendererFlip p_flip);
    void renderSpike(SDL_Texture* p_tex, float p_x, float p_y, SDL_Rect& p_clip, SDL_Rect& p_camera, double p_angle, SDL_Point* p_center, SDL_RendererFlip p_flip);

    //ve tile
    void renderTile(Entity& p_entity, SDL_Rect& p_clip, SDL_Rect& camera);
    void renderText(Entity& entity, SDL_Rect* rec = NULL, SDL_Rect* camera = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void renderTexture(SDL_Texture* p_tex, float p_x, float p_y, float p_w = 0, float p_h = 0, SDL_Rect* rec = NULL, SDL_Rect* camera = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void openFont(const char* filePath);
    SDL_Texture* loadText(string p_text, SDL_Color p_textColor);

    void display();
    static bool checkCollision(SDL_Rect a, SDL_Rect b);
    bool checkTileCollsionX(SDL_Rect& p_collision, vector<Map>& p_maps, RenderWindow& p_renderwindow, bool& isDead);
    bool checkTileCollsionY(SDL_Rect& p_collision, vector<Map>& p_maps, RenderWindow& p_renderwindow, bool& p_grounded, int& p_groundIndex, bool& isDead, int& p_mapIndex);
    
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};