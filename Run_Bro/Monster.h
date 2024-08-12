#pragma once
#include "Entity.h"
#include "Renderwindow.h"
#include "Player.h"

class Monster : public Entity {
public:
    Monster(float p_x, float p_y, SDL_Texture* p_tex);
    void update();
    void takeHit();
    void render(RenderWindow& p_renderwindow);
    void moveToPlayer(Player& p_player);
    void autoMove();
    SDL_Rect getCollision();

private:
    //player size
    const int MONSTER_WIDTH = 64;
    const int MONSTER_HEIGHT = 64;
    const int MONSTER_VEL = 4;

    //cac animation
    static const int IDLING_ANIMATIONS_FRAME = 4;
    static const int RUNNING_ANIMATIONS_FRAME = 8;
    static const int ATTACKING_ANIMATIONS_FRAME = 8;
    static const int DEATH_ANIMATIONS_FRAME = 4;
    static const int TAKEHIT_ANIMATIONS_FRAME = 4;

    //cac frame
    SDL_Rect idlingClips[IDLING_ANIMATIONS_FRAME];
    SDL_Rect runningClips[RUNNING_ANIMATIONS_FRAME];
    SDL_Rect attackingClips[ATTACKING_ANIMATIONS_FRAME];
    SDL_Rect deathClips[DEATH_ANIMATIONS_FRAME];
    SDL_Rect takingHitClips[DEATH_ANIMATIONS_FRAME];

    int idleFrame = 0, runFrame = 0, attackFrame, deathFrame = 0, takeHitFrame = 0;

    float velX = 0, velY = 0;

    int health = 3;
    int groundIndex = 1, mapIndex = 1;
    bool grounded = false, isIdling = true, isRunning = false, isJumping = false, isFalling = true, isAttacking = false, isDead = false;

    SDL_Rect collision;
};