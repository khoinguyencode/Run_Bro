#include "Player.h"
#include <iostream>
using namespace std;

Player::Player(float p_x, float p_y, SDL_Texture* p_tex) : Entity(p_x, p_y, p_tex) {
    for (int i = 0; i < IDLING_ANIMATIONS_FRAME; ++i) {
        idlingClips[i].x = i * PLAYER_WIDTH;
        idlingClips[i].y = 0;
        idlingClips[i].w = PLAYER_WIDTH;
        idlingClips[i].h = PLAYER_HEIGHT;
    }

    for (int i = 0; i < RUNNING_ANIMATIONS_FRAME; ++i) {
        runningClips[i].x = i * PLAYER_WIDTH;
        runningClips[i].y = 0;
        runningClips[i].w = PLAYER_WIDTH;
        runningClips[i].h = PLAYER_HEIGHT;
    }

    for (int i = 0; i < JUMPING_ANIMATIONS_FRAME; ++i) {
        jumpingClips[i].x = i * PLAYER_WIDTH;
        jumpingClips[i].y = 0;
        jumpingClips[i].w = PLAYER_WIDTH;
        jumpingClips[i].h = PLAYER_HEIGHT;
    }

    for (int i = 0; i < FALLING_ANIMATIONS_FRAME; ++i) {
        fallingClips[i].x = i * PLAYER_WIDTH;
        fallingClips[i].y = 0;
        fallingClips[i].w = PLAYER_WIDTH;
        fallingClips[i].h = PLAYER_HEIGHT;
    }

    for (int i = 0; i < ATTACKING_ANIMATIONS_FRAME; ++i) {
        attackingClips[i].x = i * PLAYER_WIDTH;
        attackingClips[i].y = 0;
        attackingClips[i].w = PLAYER_WIDTH;
        attackingClips[i].h = PLAYER_HEIGHT;
    }

    for (int i = 0; i < DEATH_ANIMATIONS_FRAME; ++i) {
        deathClips[i].x = i * PLAYER_WIDTH;
        deathClips[i].y = 0;
        deathClips[i].w = PLAYER_WIDTH;
        deathClips[i].h = PLAYER_HEIGHT;
    }
}

void Player::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
        case SDLK_RIGHT:
            velX += PLAYER_VEL;
            break;
        case SDLK_LEFT:
            velX -= PLAYER_VEL;
            break;
        case SDLK_UP:
            break;
        case SDLK_SPACE:
            break;
        default:
            break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
        case SDLK_RIGHT:
            velX -= PLAYER_VEL;
            break;
        case SDLK_LEFT:
            velX += PLAYER_VEL;
            break;
        case SDLK_UP:
            velY += PLAYER_VEL;
            break;
        case SDLK_SPACE:
            break;
        default:
            break;
        }
    }
}

void Player::update() {
    currentFrame = idlingClips[frame / 8];
    ++frame;
    if (frame / 8 >= IDLING_ANIMATIONS_FRAME) frame = 0;

    //if (velX == 0 && grounded && !isDead) isIdling = true;
    //else isIdling = false;

    //if (velX != 0 && grounded && !isDead) isRunning = true;
    //else isRunning = false;

    //if (velY > 0 && !grounded && !isDead) isFalling = true;
    //else isFalling = false;

    //if (velY <= 0 && !grounded && !isDead) isJumping = true;
    //else isJumping = false;

}