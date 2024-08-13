#include "Monster.h"

Monster::Monster(float p_x, float p_y, SDL_Texture* p_tex) : Entity(p_x, p_y, p_tex){
	collision.w = MONSTER_WIDTH;
	collision.h = MONSTER_HEIGHT;

	for (int i = 0; i < IDLING_ANIMATIONS_FRAME; i++) {
		idlingClips[i].x = i * (currentFrame.w / 4);
		idlingClips[i].y = 0;
		idlingClips[i].w = currentFrame.w / 4;
		idlingClips[i].h = currentFrame.h / 7;
	}
	for (int i = 0; i < RUNNING_ANIMATIONS_FRAME; i++) {
		if (i < 4) {
			runningClips[i].x = i * (currentFrame.w / 4);
			runningClips[i].y = (currentFrame.h / 7);
		}
		else {
			runningClips[i].x = (i - 4) * (currentFrame.w / 4);
			runningClips[i].y = (currentFrame.h / 7) * 2;
		}
		runningClips[i].w = currentFrame.w / 4;
		runningClips[i].h = currentFrame.h / 7;
	}
	for (int i = 0; i < ATTACKING_ANIMATIONS_FRAME; i++) {
		if (i < 4) {
			attackingClips[i].x = i * (currentFrame.w / 4);
			attackingClips[i].y = (currentFrame.h / 7) * 3;
		}
		else {
			attackingClips[i].x = (i - 4) * (currentFrame.w / 4);
			attackingClips[i].y = (currentFrame.h / 7) * 4;
		}
		attackingClips[i].w = currentFrame.w / 4;
		attackingClips[i].h = currentFrame.h / 7;
	}
	for (int i = 0; i < TAKINGHIT_ANIMATIONS_FRAME; i++) {
		takingHitClips[i].x = i * (currentFrame.w / 4);
		takingHitClips[i].y = (currentFrame.h / 7) * 5;
		takingHitClips[i].w = currentFrame.w / 4;
		takingHitClips[i].h = currentFrame.h / 7;
	}
	for (int i = 0; i < DEATH_ANIMATIONS_FRAME; i++) {
		deathClips[i].x = i * (currentFrame.w / 4);
		deathClips[i].y = (currentFrame.h / 7) * 6;
		deathClips[i].w = currentFrame.w / 4;
		deathClips[i].h = currentFrame.h / 7;
	}
}

bool Monster::getDead() {
	return deathFrame / 8 >= 3.2;
}

SDL_Rect Monster::getCollision() const{
	return collision;
}

float Monster::getDistance() {
	return distance;
}

bool Monster::getAttacking() {
	return attackFrame / 4 >= 2;
}

void Monster::gravity() {
	if (!grounded) {
		velY += 0.3;
		if (velY > 15.0) velY = 15.0;
	}
	else velY = 0.3;
}

void Monster::autoMoveToPlayer(Player& p_player, vector<Map>& p_maps) {
	//cong thuc tinh khoang cach Euclid giua 2 diem trong khong gian (giua nguoi choi va quai)
	distance = sqrt(((p_player.getX() - getX()) * (p_player.getX() - getX())) + (p_player.getY() - getY()) * (p_player.getY() - getY()));
	if (!takingHit && !isDead) {
		//neu quai nhin thay trong pham vi 7 tile
		if (distance <= TILE_WIDTH * 7 && (p_player.getY() >= y - TILE_WIDTH && p_player.getY() <= y + TILE_WIDTH / 2.0)) {
			//player nam ben phai quai
			if (p_player.getX() - x < 0) {
				//kiem tra tile ben trai xem co phai vat can khong, neu co thi quay lai
				if (p_maps[mapIndex].getTiles()[groundIndex - 1]->getType() > 40) velX = 0;
				else velX = -MONSTER_VEL;
			}
			else {
				//kiem tra tile ben phai xem co phai vat can khong, neu co thi quay lai
				if (p_maps[mapIndex].getTiles()[groundIndex + 1]->getType() > 40) velX = 0;
				else velX = MONSTER_VEL;
			}
		}
	}
	//neu du gan thi quai se danh
	if (!isDead && !takingHit && grounded && (distance <= TILE_WIDTH * 1.5 || (p_player.getY() >= y - TILE_WIDTH * 2.5 && p_player.getY() <= y - 64 && distance <= TILE_WIDTH * 2.5))) isAttacking = true;
	else isAttacking = false;
}

//tu dong di chuyen neu khong thay player
void Monster::autoMove(vector<Map>& p_maps) {
	if (!isDead && grounded && !takingHit) {
		if (p_maps[mapIndex].getTiles()[groundIndex + 1]->getType() > 40 && velX > 0) velX = -MONSTER_VEL / 2.0;
		else if (p_maps[mapIndex].getTiles()[groundIndex - 1]->getType() > 40 && velX < 0) velX = MONSTER_VEL / 2.0;
		else if (p_maps[mapIndex].getTiles()[groundIndex + 1]->getType() > 40 && p_maps[mapIndex].getTiles()[groundIndex - 2]->getType() > 40) velX = 0;
		else if (p_maps[mapIndex].getTiles()[groundIndex + 2]->getType() > 40 && p_maps[mapIndex].getTiles()[groundIndex - 2]->getType() > 40) velX = 0;
		else {
			if (flipType == SDL_FLIP_NONE) velX = MONSTER_VEL / 2.0;
			else if (flipType == SDL_FLIP_HORIZONTAL) velX = -MONSTER_VEL / 2.0;
		}
	}
}

void Monster::update(RenderWindow& p_renderwindow, vector<Map>& p_maps, SDL_Rect& p_camera, Player& p_player) {
	gravity();
	autoMove(p_maps);
	autoMoveToPlayer(p_player, p_maps);
	beingHit(p_camera, p_player);
	getHit();
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
		p_renderwindow.renderAnimation(*this, attackingClips[attackFrame / 2], p_camera, 0, NULL, flipType);
		attackFrame++;
		if (attackFrame / 2 >= ATTACKING_ANIMATIONS_FRAME) attackFrame = 0;
	}
	else attackFrame = 0;

	if (takingHit) {
		p_renderwindow.renderAnimation(*this, takingHitClips[takeHitFrame / 8], p_camera, 0, NULL, flipType);
		takeHitFrame++;
	}
	else takeHitFrame = 0;

	if (isDead) {
		p_renderwindow.renderAnimation(*this, deathClips[deathFrame / 8], p_camera, 0, NULL, flipType);
		if (deathFrame / 8 < DEATH_ANIMATIONS_FRAME - 1) deathFrame++;
	}
	else deathFrame = 0;
}

void Monster::beingHit(SDL_Rect& p_camera, Player& p_player) {
	//quai trong tam cua player
	if (distance <= 2.0 * TILE_WIDTH && p_player.getAttacking() && y >= p_player.getY() - TILE_WIDTH && y <= p_player.getY() + TILE_WIDTH + 10) {
		takingHit = true;
		--health;
	}

	if (takeHitFrame / 8 >= TAKINGHIT_ANIMATIONS_FRAME) {
		takingHit = false;
		takeHitFrame = 0;
	}

	if (health < 1 || y + MONSTER_HEIGHT >= MAP_HEIGHT || x - p_camera.x <= 5) {
		isDead = true;
		takingHit = false;
	}
}

void Monster::getHit() {
	if (takingHit && takeHitFrame < 1) {
		velY = -3.2;
		if (flipType == SDL_FLIP_NONE) velY = -4;
		else if (flipType == SDL_FLIP_HORIZONTAL) velX = 4;
	}
}