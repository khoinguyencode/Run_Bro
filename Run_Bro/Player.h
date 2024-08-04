#pragma once
#include "Entity.h"
#include "Renderwindow.h"
#include "Tile.h"

class Player : public Entity {
public:
    Player(float p_x, float p_y, SDL_Texture* p_tex);
    void handleEvent(SDL_Event& e);
    void jump();
    void gravity(); //keo nguoi choi xuong
    void update(RenderWindow& p_renderwindow, Map& p_map);
    void render(RenderWindow& p_renderwindow ,SDL_Rect& p_camera);
    void setCamera(SDL_Rect& p_camera);
private:
    //player size
    const int PLAYER_WIDTH = 64;
    const int PLAYER_HEIGHT = 64;
    const int PLAYER_VEL = 6;

    //cac animation
    static const int IDLING_ANIMATIONS_FRAME = 8;
    static const int RUNNING_ANIMATIONS_FRAME = 8;
    static const int JUMPING_ANIMATIONS_FRAME = 4;
    static const int FALLING_ANIMATIONS_FRAME = 4;
    static const int ATTACKING_ANIMATIONS_FRAME = 3;
    static const int DEATH_ANIMATIONS_FRAME = 14;

    //cac frame
    SDL_Rect idlingClips[IDLING_ANIMATIONS_FRAME];
    SDL_Rect runningClips[RUNNING_ANIMATIONS_FRAME];
    SDL_Rect jumpingClips[JUMPING_ANIMATIONS_FRAME];
    SDL_Rect fallingClips[FALLING_ANIMATIONS_FRAME];
    SDL_Rect attackingClips[ATTACKING_ANIMATIONS_FRAME];
    SDL_Rect deathClips[DEATH_ANIMATIONS_FRAME];

    int idleFrame = 0, runFrame = 0, jumpFrame = 0, fallFrame = 0, attackFrame, deathFrame = 0;

    float velX = 0, velY = 0;

    int groundIndex = 1;
    bool grounded = false, isIdling = true, isRunning = false, isJumping = false, isFalling = true, isAttacking = false, isDead = false;

    SDL_Rect collision;
};
