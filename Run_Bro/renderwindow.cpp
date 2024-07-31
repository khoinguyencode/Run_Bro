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

SDL_Renderer* RenderWindow::getRenderer() const {
	return renderer;
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
	dst.w = p_clip.w * 2;
	dst.h = p_clip.h * 2;
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

bool RenderWindow::touchesWall(SDL_Rect box, Tile* tiles[])
{
	//Go through the tiles
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		//If the tile is a wall type tile
		if ((tiles[i]->getType() >= TILE_CENTER) && (tiles[i]->getType() <= TILE_TOPLEFT))
		{
			//If the collision box touches the wall tile
			if (checkCollision(box, tiles[i]->getBox())) {
				return true;
			}
		}
	}

	//If no wall tiles were touched
	return false;
}


