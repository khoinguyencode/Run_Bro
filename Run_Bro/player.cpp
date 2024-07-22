#include "Player.h"
#include <iostream>
using namespace std;

Player::Player(float p_x, float p_y, SDL_Texture* p_tex) : Entity(p_x, p_y, p_tex){

    idleTex = p_tex; // Set the initial texture to idle

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

void Player::setTextures(SDL_Texture* idle, SDL_Texture* run, SDL_Texture* jump, SDL_Texture* fall, SDL_Texture* attack, SDL_Texture* death) {
    idleTex = idle;
    runTex = run;
    jumpTex = jump;
    fallTex = fall;
    attackTex = attack;
    deathTex = death;
}

void Player::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
        case SDLK_RIGHT:
            rightPressed = true;
            velX += PLAYER_VEL;
            flipType = SDL_FLIP_NONE;
            isRunning = true;
            isJumping = false;
            isFalling = false;
            isAttacking = false;
            isDead = false;
            tex = runTex;
            break;
        case SDLK_LEFT:
            leftPressed = true;
            velX -= PLAYER_VEL;
            flipType = SDL_FLIP_HORIZONTAL;
            isRunning = true;
            isJumping = false;
            isFalling = false;
            isAttacking = false;
            isDead = false;
            tex = runTex;
            break;
        case SDLK_UP:
            upPressed = true;
            if (grounded) {
                jump();
            }
            isJumping = true;
            isRunning = false;
            isFalling = false;
            isAttacking = false;
            isDead = false;
            tex = jumpTex;
            break;
        case SDLK_SPACE:
            spacePressed = true;
            isAttacking = true;
            isRunning = false;
            isJumping = false;
            isFalling = false;
            isDead = false;
            tex = attackTex;
            break;
        default:
            break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
        case SDLK_RIGHT:
            rightPressed = false;
            velX -= PLAYER_VEL;
            break;
        case SDLK_LEFT:
            leftPressed = false;
            velX += PLAYER_VEL;
            break;
        case SDLK_UP:
            upPressed = false;
            velY += PLAYER_VEL;
            break;
        case SDLK_SPACE:
            spacePressed = false;
            break;
        default:
            break;
        }
    }

    // Kiểm tra trạng thái các phím
    if (spacePressed) {
        isAttacking = true;
        tex = attackTex;
    }
    else if (upPressed) {
        isJumping = true;
        tex = jumpTex;
    }
    else if (rightPressed || leftPressed) {
        isRunning = true;
        tex = runTex;
    }
    else {
        isRunning = false;
        isJumping = false;
        isFalling = false;
        isAttacking = false;
        isDead = false;
        tex = idleTex;
    }
}


void Player::update() {
    gravity();
    x += velX;
    y += velY;

    if (isAttacking) {
        updateAttack();
    }
    else if (isJumping) {
        updateJump();
    }
    else if (isFalling) {
        updateFall();
    }
    else if (isRunning) {
        updateRun();
    }
    else if (isDead) {
        updateDeath();
    }
    else {
        updateIdle();
    }
}


void Player::updateIdle() {
    currentFrame = idlingClips[frame / 8];
    ++frame;
    if (frame / 8 >= IDLING_ANIMATIONS_FRAME) {
        frame = 0;
    }
}

void Player::updateRun() {
    currentFrame = runningClips[frame / 8];
    ++frame;
    if (frame / 8 >= RUNNING_ANIMATIONS_FRAME) {
        frame = 0;
    }
}

void Player::updateJump() {
    currentFrame = jumpingClips[frame / 2];
    ++frame;
    if (frame / 2 >= JUMPING_ANIMATIONS_FRAME) {
        frame = 0;
    }
}

void Player::updateFall() {
    currentFrame = fallingClips[frame / 2];
    ++frame;
    if (frame / 2 >= FALLING_ANIMATIONS_FRAME) {
        frame = 0;
    }
}

void Player::updateAttack() {
    currentFrame = attackingClips[frame];
    ++frame;
    if (frame >= ATTACKING_ANIMATIONS_FRAME) {
        frame = 0;
    }
}

void Player::updateDeath() {
    currentFrame = deathClips[frame / 6];
    ++frame;
    if (frame / 6 >= DEATH_ANIMATIONS_FRAME) {
        frame = 0;
    }
}

void Player::jump() {
    if (grounded) {
        velY -= 10;
        grounded = false;
    }
}

void Player::gravity() {
    if (!grounded) {
        velY += GRAVITY;
        if (velY > MAX_GRAVITY) velY = MAX_GRAVITY;
    }
    else velY = GRAVITY;
}
