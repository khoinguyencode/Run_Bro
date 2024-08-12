#include "Monster.h"

Monster::Monster(float p_x, float p_y, SDL_Texture* p_tex) : Entity(p_x, p_y, p_tex){
	collision.w = MONSTER_WIDTH;
	collision.h = MONSTER_HEIGHT;

	for (int i = 0; i < IDLING_ANIMATIONS_FRAME; i++) {
		idlingClips[i].x = i * (currentFrame.w / 4);
		idlingClips[i].y = 0;
		idlingClips[i].w = currentFrame.w / 4;
		idlingClips[i].h = currentFrame.h / 6;
	}
	for (int i = 0; i < RUNNING_ANIMATIONS_FRAME; i++) {
		runningClips[i].x = i * (currentFrame.w / 4);
		if (i < 4) runningClips[i].y = i * (currentFrame.h / 6);
		else runningClips[i].y = i * (currentFrame.h / 6) * 2;
		runningClips[i].w = currentFrame.w / 4;
		runningClips[i].h = currentFrame.h / 6;
	}
	for (int i = 0; i < ATTACKING_ANIMATIONS_FRAME; i++) {
		attackingClips[i].x = i * (currentFrame.w / 4);
		if(i < 4) attackingClips[i].y = (currentFrame.h / 6) * 3;
		else attackingClips[i].y = (currentFrame.h / 6) * 4;
		attackingClips[i].w = currentFrame.w / 4;
		attackingClips[i].h = currentFrame.h / 6;
	}
	for (int i = 0; i < TAKINGHIT_ANIMATIONS_FRAME; i++) {
		takingHitClips[i].x = i * (currentFrame.w / 4);
		takingHitClips[i].y = (currentFrame.h / 6) * 5;
		takingHitClips[i].w = currentFrame.w / 4;
		takingHitClips[i].h = currentFrame.h / 6;
	}
}

bool Monster::getDead() {
	return isDead;
}

SDL_Rect Monster::getCollision() const{
	return collision;
}

void Monster::gravity() {
	if (!grounded) {
		velY += 0.3;
		if (velY > 15.0) velY = 15.0;
	}
	else velY = 0.3;
}

void Monster::update(RenderWindow& p_renderwindow, vector<Map>& p_maps, SDL_Rect& camera) {
	gravity();
	//update trang thai monster
	isIdling = (velX == 0 && grounded && !isAttacking && !isDead && !takingHit);

	isRunning = (velX != 0 && grounded && !isAttacking && !isDead && !takingHit);

	isFalling = (velY > 0 && !grounded && !isDead && !takingHit);

	//check va cham phuong x
	if (!isAttacking && !isDead) {
		x += velX;
		collision.x = x + MONSTER_WIDTH;
		if (p_renderwindow.checkTileCollsionX(collision, p_maps, p_renderwindow, isDead)) {
			x -= velX;
			collision.x = x + MONSTER_WIDTH;
		}
	}

	//check va cham phuong y
	y += velY;
	collision.y = y + MONSTER_HEIGHT;
	if (p_renderwindow.checkTileCollsionY(collision,p_maps, p_renderwindow ,grounded, groundIndex, isDead, mapIndex)) {
		if (velY > 0) {
			//set lai y
			y = p_maps[mapIndex].getTiles()[groundIndex]->getY() - 64 * 2;
			if (isFalling) grounded = true;
		}
		else if (velY > 0) {
			y -= velY;
			velY = 0;
		}
		collision.y = y + MONSTER_HEIGHT;
	}
	if (velX < 0) flipType = SDL_FLIP_HORIZONTAL;
	if (velX > 0) flipType = SDL_FLIP_NONE;
}


void Monster::render(RenderWindow& p_renderwindow, SDL_Rect& p_camera) {
	if (isIdling) {
		p_renderwindow.renderAnimation(*this, idlingClips[idleFrame / 8], p_camera, 0, NULL, flipType);
		idleFrame++;
		if (idleFrame / 8 >= IDLING_ANIMATIONS_FRAME) idleFrame = 0;
	}
	else idleFrame = 0;

	if (isRunning) {
		p_renderwindow.renderAnimation(*this, runningClips[runFrame / 8], p_camera, 0, NULL, flipType);
		runFrame++;
		if (runFrame / 8 >= RUNNING_ANIMATIONS_FRAME) runFrame = 0;
	}

	if (isFalling) {
		p_renderwindow.renderAnimation(*this, idlingClips[0], p_camera, 0, NULL, flipType);
	}

	if (isAttacking) {
		p_renderwindow.renderAnimation(*this, attackingClips[attackFrame / 8], p_camera, 0, NULL, flipType);
		attackFrame++;
		if (attackFrame / 8 >= ATTACKING_ANIMATIONS_FRAME) attackFrame = 0;
	}
	else attackFrame = 0;

	if (takingHit) {
		p_renderwindow.renderAnimation(*this, takingHitClips[takeHitFrame / 7], p_camera, 0, NULL, flipType);
		takeHitFrame++;
	}
	else takeHitFrame = 0;
}

