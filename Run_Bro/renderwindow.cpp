#include "Renderwindow.h"
#include "Entity.h"
#include <iostream>
using namespace std;

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		cout << "Window failed to init. Error: " << SDL_GetError << endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath) {
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
		cout << "Failed to load texture. Error: " << SDL_GetError << endl;

	return texture;
}

void RenderWindow::cleanUp() {
	SDL_DestroyWindow(window);
}

void RenderWindow::clear() {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity) {
	// xac dinh phan cua texture duoc ve
	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	// xac dinh vi tri va kich thuoc hinh chu nhat noi chua texture
	SDL_Rect dst;
	dst.x = p_entity.getX();
	dst.y = p_entity.getY();
	dst.w = p_entity.getCurrentFrame().w * 4;
	dst.h = p_entity.getCurrentFrame().h * 4;

	SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}


void RenderWindow::renderAnimation(Entity& p_entity, SDL_Rect& p_clip, SDL_Rect& p_camera, double p_angle, SDL_Point* p_center, SDL_RendererFlip p_flip) {
	//xac dinh phan cua texture duoc ve
	SDL_Rect src;
	src.x = p_clip.x;
	src.y = p_clip.y;
	src.w = p_clip.w;
	src.h = p_clip.h;

	//xac dinh vi tri va kich thuoc hinh chu nhat duoc ve len man hinh
	SDL_Rect dst;
	dst.x = p_entity.getX() - p_camera.x; //Vi tri cua nhan vat tren man hinh = vi tri thuc te - vi tri camera
	dst.y = p_entity.getY() - p_camera.y;

	//scale nhan vat
	dst.w = p_clip.w;
	dst.h = p_clip.h;
	SDL_RenderCopyEx(renderer, p_entity.getTex(), &p_clip, &dst, p_angle, p_center, p_flip);
}

void RenderWindow::renderTile(Entity& p_entity, SDL_Rect& p_clip, SDL_Rect& p_camera) {
	SDL_Rect dst;
	dst.x = p_entity.getX() - p_camera.x;
	dst.y = p_entity.getY() - p_camera.y;
	dst.w = p_clip.w;
	dst.h = p_clip.h;
	SDL_RenderCopy(renderer, p_entity.getTex(), &p_clip, &dst);
}

void RenderWindow::display() {
	SDL_RenderPresent(renderer);
}

bool RenderWindow::checkCollision(SDL_Rect a, SDL_Rect b) {
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	if (bottomA <= topB) {
		return false;
	}

	if (topA >= bottomB) {
		return false;
	}

	if (rightA <= leftB) {
		return false;
	}

	if (leftA >= rightB) {
		return false;
	}

	return true;
}

bool RenderWindow::checkTileCollsionX(SDL_Rect& p_collision, vector<Map>& p_maps, RenderWindow& p_renderwindow, bool& isDead) {
	//check truoc 3 map
	for (int i = 0; i < p_maps.size(); i++) {
		if (p_collision.x > p_maps[i].getX() && p_collision.x + p_collision.w + 13 < LEVEL_WIDTH + p_maps[i].getX() && p_collision.y >= 0 && p_collision.y + TILE_HEIGHT < LEVEL_WIDTH) {
			//xac dinh cac khoang ma collsion nam trong hoac va cham
			int col_start = (p_collision.x - p_maps[i].getX()) / TILE_WIDTH;
			int col_end = col_start + 1;
			int row_start = p_collision.y / TILE_HEIGHT;
			int row_end = row_start + 1;

			//vi tri(ID) cua tile xung quanh collsion cua player = dong * Tong so cot + cot
			int indexTile1 = row_start * 21 + col_end; //dong tren cot phai
			int indexTile2 = row_end * 21 + col_end; //dong duoi cot phai
			int indexTile3 = row_start * 21 + col_start; //dong tren cot trai
			int indexTile4 = row_end * 21 + col_start; //dong duoi cot trai

			//kiem tra type cua tile
			if (indexTile1 < p_maps[i].getTiles().size()) {
				int type1 = p_maps[i].getTiles()[indexTile1]->getType();

				if (type1 >= 0 && type1 <= 40 && p_renderwindow.checkCollision(p_collision, p_maps[i].getTiles()[indexTile1]->getBox())) return true;
			}
			if (indexTile2 < p_maps[i].getTiles().size()) {
				int type2 = p_maps[i].getTiles()[indexTile2]->getType();
				
				if (type2 >= 0 && type2 <= 40 && p_renderwindow.checkCollision(p_collision, p_maps[i].getTiles()[indexTile2]->getBox())) return true;
			}
			if (indexTile3 < p_maps[i].getTiles().size()) {
				int type3 = p_maps[i].getTiles()[indexTile3]->getType();

				if (type3 >= 0 && type3 <= 40 && p_renderwindow.checkCollision(p_collision, p_maps[i].getTiles()[indexTile3]->getBox())) return true;
			}
			if (indexTile4 < p_maps[i].getTiles().size()) {
				int type4 = p_maps[i].getTiles()[indexTile4]->getType();

				if (type4 >= 0 && type4 <= 40 && p_renderwindow.checkCollision(p_collision, p_maps[i].getTiles()[indexTile4]->getBox())) return true;
			}
		}
	}
	return false;
}


bool RenderWindow::checkTileCollsionY(SDL_Rect& p_collision, vector<Map>& p_maps, RenderWindow& p_renderwindow, bool& p_grounded, int& p_groundIndex, bool& isDead, int& p_mapIndex) {
	bool ok = false;
	//check truoc 3 map
	for (int i = 0; i < p_maps.size(); i++) {
		if (p_collision.x + p_collision.w + 12 >= p_maps[i].getX() && p_collision.x <= LEVEL_WIDTH + p_maps[i].getX() && p_collision.y >= 0 && p_collision.y + TILE_HEIGHT < LEVEL_WIDTH) {
			//xac dinh cac khoang ma collsion nam trong hoac va cham
			int col_start = (p_collision.x - p_maps[i].getX()) / TILE_WIDTH;
			int col_end = col_start + 1;
			int row_start = p_collision.y / TILE_HEIGHT;
			int row_end = row_start + 1;

			//vi tri(ID) cua tile xung quanh collsion cua player = dong * Tong so cot + cot
			int indexTile1 = row_start * 21 + col_end; //dong tren cot phai
			int indexTile2 = row_end * 21 + col_end; //dong duoi cot phai
			int indexTile3 = row_start * 21 + col_start; //dong tren cot trai
			int indexTile4 = row_end * 21 + col_start; //dong duoi cot trai

			//kiem tra type cua tile
			if (p_collision.x <= p_maps[i].getX() && p_collision.x + p_collision.w + 12 >= p_maps[i].getX() || p_collision.x <= p_maps[i].getX() + LEVEL_WIDTH && p_collision.x + p_collision.w + 12 >= p_maps[i].getX() + LEVEL_WIDTH) {
				p_grounded = false;
			}
			else {
				if (indexTile1 < p_maps[i].getTiles().size()) {
					int type1 = p_maps[i].getTiles()[indexTile1]->getType();

					if (type1 >= 0 && type1 <= 40 && p_renderwindow.checkCollision(p_maps[i].getTiles()[indexTile1]->getBox(), p_collision)) ok = true;
				}
				if (indexTile2 < p_maps[i].getTiles().size()) {
					int type2 = p_maps[i].getTiles()[indexTile2]->getType();

					if (type2 >= 0 && type2 <= 40 && p_renderwindow.checkCollision(p_maps[i].getTiles()[indexTile2]->getBox(), p_collision)) ok = true;
				}
				if (indexTile3 < p_maps[i].getTiles().size()) {
					int type3 = p_maps[i].getTiles()[indexTile3]->getType();

					if (type3 >= 0 && type3 <= 40 && p_renderwindow.checkCollision(p_maps[i].getTiles()[indexTile3]->getBox(), p_collision)) ok = true;
				}
				if (indexTile4 < p_maps[i].getTiles().size()) {
					int type4 = p_maps[i].getTiles()[indexTile4]->getType();

					if (type4 >= 0 && type4 <= 40 && p_renderwindow.checkCollision(p_maps[i].getTiles()[indexTile4]->getBox(), p_collision)) ok = true;
				}
				if (indexTile2 < p_maps[i].getTiles().size() && indexTile4 < p_maps[i].getTiles().size()) {
					if ((p_maps[i].getTiles()[indexTile2]->getType() > 40) && (p_maps[i].getTiles()[indexTile4]->getType() > 40)) p_grounded = false;
					if ((p_maps[i].getTiles()[indexTile4]->getType() > 40) && (p_maps[i].getTiles()[indexTile2]->getType() <= 40) && p_collision.x + p_collision.w <= p_maps[i].getTiles()[indexTile2]->getX()) p_grounded = false;
				}
			}
			p_groundIndex = indexTile4;
			p_mapIndex = i;
		}
	}
	return ok;
}

