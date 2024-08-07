#include "Player.h"
#include <iostream>
using namespace std;

Player::Player(float p_x, float p_y, SDL_Texture* p_tex) : Entity(p_x, p_y, p_tex) {
    collision.w = PLAYER_WIDTH;
    collision.h = PLAYER_HEIGHT;

    for (int i = 0; i < IDLING_ANIMATIONS_FRAME; ++i) {
        idlingClips[i].x = i * PLAYER_WIDTH;
        idlingClips[i].y = 0;
        idlingClips[i].w = PLAYER_WIDTH;
        idlingClips[i].h = PLAYER_HEIGHT;
    }

    for (int i = 0; i < RUNNING_ANIMATIONS_FRAME; ++i) {
        runningClips[i].x = i * PLAYER_WIDTH;
        runningClips[i].y = PLAYER_HEIGHT;
        runningClips[i].w = PLAYER_WIDTH;
        runningClips[i].h = PLAYER_HEIGHT;
    }

    for (int i = 0; i < JUMPING_ANIMATIONS_FRAME; ++i) {
        jumpingClips[i].x = i * PLAYER_WIDTH;
        jumpingClips[i].y = PLAYER_HEIGHT * 4;
        jumpingClips[i].w = PLAYER_WIDTH;
        jumpingClips[i].h = PLAYER_HEIGHT;
    }

    for (int i = 0; i < FALLING_ANIMATIONS_FRAME; ++i) {
        fallingClips[i].x = i * PLAYER_WIDTH;
        fallingClips[i].y = PLAYER_HEIGHT * 5;
        fallingClips[i].w = PLAYER_WIDTH;
        fallingClips[i].h = PLAYER_HEIGHT;
    }

    for (int i = 0; i < ATTACKING_ANIMATIONS_FRAME; ++i) {
        attackingClips[i].x = i * PLAYER_WIDTH;
        attackingClips[i].y = PLAYER_HEIGHT * 3;
        attackingClips[i].w = PLAYER_WIDTH;
        attackingClips[i].h = PLAYER_HEIGHT;
    }

    for (int i = 0; i < DEATH_ANIMATIONS_FRAME; ++i) {
        deathClips[i].x = i * PLAYER_WIDTH;
        deathClips[i].y = PLAYER_HEIGHT * 7;
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
            jump();
            break;
        case SDLK_SPACE:
            isAttacking = true;
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
            if (!grounded && isJumping) {
                velY /= 2.0;
            }
            break;
        case SDLK_SPACE:
            isAttacking = false; 
            break;
        default:
            break;
        }
    }
}

void Player::jump() {
    if (grounded) {
        velY -= 12; // toc do nhay
        grounded = false;
    }
}

void Player::gravity() {
    if (!grounded) {
        velY += 0.3;
        if (velY > 15.0) velY = 15.0;
    }
    else velY = 2;
}

void Player::update(RenderWindow& p_renderwindow, Map& p_map) {
    gravity();

    if (!isDead) {
        isIdling = (velX == 0 && grounded && !isAttacking);
        isRunning = (velX != 0 && grounded && !isAttacking);
        isJumping = (velY <= 0 && !grounded && !isAttacking);
        isFalling = (velY > 0 && !grounded && !isAttacking);
    }

    //check X collsion
    x += velX;
    collision.x = x + PLAYER_WIDTH - 8;
    if (x + PLAYER_WIDTH < 0) {
        x = -PLAYER_WIDTH;
        collision.x = x + PLAYER_WIDTH;
    }
    if (p_renderwindow.checkTileCollsionX(collision, p_map, p_renderwindow)) {
        x -= velX;
        collision.x = x + PLAYER_WIDTH - 12;
    }

    //check Y collsion
    y += velY;
    collision.y = y + PLAYER_HEIGHT;
    if (y + PLAYER_HEIGHT < 0) {
        y = -PLAYER_HEIGHT;
        collision.y = y + PLAYER_HEIGHT;
    }
    if(p_renderwindow.checkTileCollsionY(collision, p_map, p_renderwindow, grounded, groundIndex)){
        if (velY > 0) {
            y = p_map.getTiles()[groundIndex]->getY() - 64 * 2;
            if (isFalling) grounded = true;
        } 
        else if (velY < 0) {
            y -= velY;
            velY = 0;
        }
        collision.y = y + PLAYER_HEIGHT;
    }

    if (velX > 0) flipType = SDL_FLIP_NONE;
    if (velX < 0) flipType = SDL_FLIP_HORIZONTAL;


    /*cout << "Player grounded: " << grounded << " isFalling: " << isFalling << " velY: " << velY << endl;*/
    /*cout << "Player position: (" << x << ", " << y << ")" << endl;*/
}


void Player::render(RenderWindow& p_renderwindow, SDL_Rect& p_camera) {
    if (isIdling) {
        p_renderwindow.renderAnimation(*this, idlingClips[idleFrame / 4], p_camera, 0, NULL, flipType);
        idleFrame++;
        if (idleFrame / 4 >= IDLING_ANIMATIONS_FRAME) idleFrame = 0;
    }
    else idleFrame = 0;

    if (isRunning) {
        p_renderwindow.renderAnimation(*this, runningClips[runFrame / 6], p_camera, 0, NULL, flipType);
        runFrame++;
        if (runFrame / 6 >= RUNNING_ANIMATIONS_FRAME) runFrame = 0;
    }
    else runFrame = 0;

    if (isAttacking) {
        p_renderwindow.renderAnimation(*this, attackingClips[attackFrame / 3], p_camera, 0, NULL, flipType);
        attackFrame++;
        if (attackFrame / 3 >= ATTACKING_ANIMATIONS_FRAME) attackFrame = 0;
    }
    else attackFrame = 0;

    if (isJumping) {
        p_renderwindow.renderAnimation(*this, jumpingClips[jumpFrame / 8], p_camera, 0, NULL, flipType);
        jumpFrame++;
        if (jumpFrame / 8 >= JUMPING_ANIMATIONS_FRAME) jumpFrame = 0;
    }
    else jumpFrame = 0;

    if (isFalling) {
        p_renderwindow.renderAnimation(*this, fallingClips[fallFrame / 4], p_camera, 0, NULL, flipType);
        fallFrame++;
        if (fallFrame / 4 >= FALLING_ANIMATIONS_FRAME) fallFrame = 0;
    }
    else fallFrame = 0;

    if (isDead) {
        p_renderwindow.renderAnimation(*this, deathClips[deathFrame / 8], p_camera, 0, NULL, flipType);
        if (deathFrame / 8 < DEATH_ANIMATIONS_FRAME - 1) deathFrame++;
    }
    else deathFrame = 0;
}

void Player::setCamera(SDL_Rect& p_camera) {
    p_camera.x = (collision.x + PLAYER_WIDTH / 2) - SCREEN_WIDTH / 2;
    p_camera.y = (collision.y + PLAYER_HEIGHT / 2) - SCREEN_HEIGHT / 2;

    //Giu cho camera luon nam trong vong
    if (p_camera.x < 0) p_camera.x = 0;
    if (p_camera.y < 0) p_camera.y = 0;
    if (p_camera.x > LEVEL_WIDTH - p_camera.w) p_camera.x = LEVEL_WIDTH - p_camera.w;
    if (p_camera.y > LEVEL_HEIGHT - p_camera.h) p_camera.y = LEVEL_HEIGHT - p_camera.h;
}
