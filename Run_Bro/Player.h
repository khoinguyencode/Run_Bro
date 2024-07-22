#pragma once
#include "Entity.h"
#include "Renderwindow.h"

class Player : public Entity {
public:
    Player(float p_x, float p_y, SDL_Texture* p_tex);
    void handleEvent(SDL_Event& e);
    void update();
    void updateIdle();
    void updateRun();
    void updateJump();
    void updateFall();
    void updateAttack();
    void updateDeath();
    void gravity();
    void jump();
    void setTextures(SDL_Texture* idle, SDL_Texture* run, SDL_Texture* jump, SDL_Texture* fall, SDL_Texture* attack, SDL_Texture* death);
    SDL_Rect getCollision() const {
        return collision;
    }
private:
    static const int PLAYER_WIDTH = 200;
    static const int PLAYER_HEIGHT = 200;
    static const int PLAYER_VEL = 6;

    static const int IDLING_ANIMATIONS_FRAME = 8;
    static const int RUNNING_ANIMATIONS_FRAME = 8;
    static const int JUMPING_ANIMATIONS_FRAME = 2;
    static const int FALLING_ANIMATIONS_FRAME = 2;
    static const int ATTACKING_ANIMATIONS_FRAME = 6;
    static const int DEATH_ANIMATIONS_FRAME = 6;

    SDL_Rect idlingClips[IDLING_ANIMATIONS_FRAME];
    SDL_Rect runningClips[RUNNING_ANIMATIONS_FRAME];
    SDL_Rect jumpingClips[JUMPING_ANIMATIONS_FRAME];
    SDL_Rect fallingClips[FALLING_ANIMATIONS_FRAME];
    SDL_Rect attackingClips[ATTACKING_ANIMATIONS_FRAME];
    SDL_Rect deathClips[DEATH_ANIMATIONS_FRAME];

    int frame = 0;
    int velX = 0, velY = 0;

    bool grounded = false, isRunning = false, isJumping = false, isFalling = true, isAttacking = false, isDead = false;
    SDL_Rect collision;

    bool rightPressed = false;
    bool leftPressed = false;
    bool upPressed = false;
    bool spacePressed = false;


    SDL_Texture* idleTex;
    SDL_Texture* runTex;
    SDL_Texture* jumpTex;
    SDL_Texture* fallTex;
    SDL_Texture* attackTex;
    SDL_Texture* deathTex;
};
