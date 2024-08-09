#pragma once
#include "Entity.h"
#include "Tile.h"
#include "Map.h"
#include <vector>
using namespace std;
//kich co screen
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

//kich co level
const int LEVEL_WIDTH = 1536; //1 pixel width cua 1 tile(64) x so cot(24)
const int LEVEL_HEIGHT = 1024; //1 pixel height cua 1 tile(64) x so dong(16)

class Tile;
class Map;

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
    bool checkTileCollsionX(SDL_Rect& p_collision, vector<Map>& p_maps, RenderWindow& p_renderwindow, bool& isDead);
    bool checkTileCollsionY(SDL_Rect& p_collision, vector<Map>& p_maps, RenderWindow& p_renderwindow, bool& p_grounded, int& p_groundIndex, bool& isDead, int& p_mapIndex);
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};