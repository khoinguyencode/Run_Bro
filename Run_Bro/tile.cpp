#include "Tile.h"
#include <fstream>
using namespace std;

SDL_Rect Tile::gTileClips[TOTAL_TILE_SPRITES];

Tile::Tile(float p_x, float p_y, SDL_Texture* p_tex, int p_type) : Entity(p_x, p_y, p_tex) {
    box.x = p_x;
    box.y = p_y;

    box.w = TILE_WIDTH;
    box.h = TILE_HEIGHT;

    type = p_type;
}

void Tile::render(SDL_Rect& camera, RenderWindow& p_renderwindow) {
    //Kiem tra va cham neu tile o tren man hinh
    if (p_renderwindow.checkCollision(camera, box))
        p_renderwindow.renderTile(*this, gTileClips[type], camera);
}

int Tile::getType() {
    return type;
}

SDL_Rect Tile::getBox() {
    return box;
}

bool Tile::setTiles(Tile* tiles[], SDL_Texture* p_tileTex)
{
	//Success flag
	bool tilesLoaded = true;

	//The tile offsets
	int x = 0, y = 0;

	//Open the map
	std::ifstream map("lazy.map");

	//If the map couldn't be loaded
	if (map.fail())
	{
		printf("Unable to load map file!\n");
		tilesLoaded = false;
	}
	else
	{
		//Initialize the tiles
		for (int i = 0; i < TOTAL_TILES; ++i)
		{
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;

			//If the was a problem in reading the map
			if (map.fail())
			{
				//Stop loading map
				printf("Error loading map: Unexpected end of file!\n");
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES))
			{
				tiles[i] = new Tile(x, y, p_tileTex, tileType);
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf("Error loading map: Invalid tile type at %d!\n", i);
				tilesLoaded = false;
				break;
			}

			//Move to next tile spot
			x += TILE_WIDTH;

			//If we've gone too far
			if (x >= LEVEL_WIDTH)
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_HEIGHT;
			}
		}

		//Clip the sprite sheet
		if (tilesLoaded) {
			gTileClips[TILE_RED] = { 0, 0, TILE_WIDTH, TILE_HEIGHT };
			gTileClips[TILE_GREEN] = { 0, 80, TILE_WIDTH, TILE_HEIGHT };
			gTileClips[TILE_BLUE] = { 0, 160, TILE_WIDTH, TILE_HEIGHT };
			gTileClips[TILE_TOPLEFT] = { 80, 0, TILE_WIDTH, TILE_HEIGHT };
			gTileClips[TILE_LEFT] = { 80, 80, TILE_WIDTH, TILE_HEIGHT };
			gTileClips[TILE_BOTTOMLEFT] = { 80, 160, TILE_WIDTH, TILE_HEIGHT };
			gTileClips[TILE_TOP] = { 160, 0, TILE_WIDTH, TILE_HEIGHT };
			gTileClips[TILE_CENTER] = { 160, 80, TILE_WIDTH, TILE_HEIGHT };
			gTileClips[TILE_BOTTOM] = { 160, 160, TILE_WIDTH, TILE_HEIGHT };
			gTileClips[TILE_TOPRIGHT] = { 240, 0, TILE_WIDTH, TILE_HEIGHT };
			gTileClips[TILE_RIGHT] = { 240, 80, TILE_WIDTH, TILE_HEIGHT };
			gTileClips[TILE_BOTTOMRIGHT] = { 240, 160, TILE_WIDTH, TILE_HEIGHT };
		}
	}

	//Close the file
	map.close();

	//If the map was loaded fine
	return tilesLoaded;
}

bool Tile::touchesWall(SDL_Rect box, Tile* tiles[], RenderWindow& p_renderwindow)
{
	//Go through the tiles
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		//If the tile is a wall type tile
		if ((tiles[i]->getType() >= TILE_CENTER) && (tiles[i]->getType() <= TILE_TOPLEFT))
		{
			//If the collision box touches the wall tile
			if (p_renderwindow.checkCollision(box, tiles[i]->getBox())) {
				return true;
			}
		}
	}

	//If no wall tiles were touched
	return false;
}