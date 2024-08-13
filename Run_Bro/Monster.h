#pragma once
#include "Entity.h"
#include "Renderwindow.h"
#include "Player.h"
#include <iostream>
using namespace std;

class Player;

class Monster : public Entity {
public:
    Monster(float p_x, float p_y, SDL_Texture* p_tex);
    //tu dong tien lai gan nguoi choi neu trong tam nhin
    void autoMoveToPlayer(Player& p_player, vector<Map>& p_maps);

    //tu dong di chuyen, gap vat can thi quay dau lai(thay vuc thi quay lai)
    void autoMove(vector<Map>& p_maps);
    void update(RenderWindow& p_renderwindow, vector<Map>& p_maps, SDL_Rect& camera, Player& p_player);
    void beingHit(SDL_Rect& p_camera, Player& p_player);
    void getHit(); //bi danh day lui ra sau
    void render(RenderWindow& p_renderwindow, SDL_Rect& p_camera);
    SDL_Rect getCollision() const;
    void gravity();
    bool getDead();
    bool getAttacking();
    float getDistance();

private:
    //player size
    const int MONSTER_WIDTH = 64;
    const int MONSTER_HEIGHT = 64;
    const int MONSTER_VEL = 4;

    //cac animation
    static const int IDLING_ANIMATIONS_FRAME = 4;
    static const int RUNNING_ANIMATIONS_FRAME = 8;
    static const int ATTACKING_ANIMATIONS_FRAME = 8;
    static const int TAKINGHIT_ANIMATIONS_FRAME = 4;
    static const int DEATH_ANIMATIONS_FRAME = 4;

    //cac frame
    SDL_Rect idlingClips[IDLING_ANIMATIONS_FRAME];
    SDL_Rect runningClips[RUNNING_ANIMATIONS_FRAME];
    SDL_Rect attackingClips[ATTACKING_ANIMATIONS_FRAME];
    SDL_Rect takingHitClips[TAKINGHIT_ANIMATIONS_FRAME];
    SDL_Rect deathClips[TAKINGHIT_ANIMATIONS_FRAME];

    int idleFrame = 0, runFrame = 0, attackFrame = 0, takeHitFrame = 0, deathFrame = 0;

    float velX = 0, velY = 0;
    float distance;

    int health = 9;
    int groundIndex = 1, mapIndex = 1;
    bool grounded = false, isIdling = true, isRunning = false, isFalling = true, isAttacking = false, isDead = false, takingHit = false;

    SDL_Rect collision;

};