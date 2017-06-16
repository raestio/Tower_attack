#include "Tile.h"
#include "../game_objects/Tower.h"
#include <string>

Tile::Tile(int posX, int posY, const SDL_Color & color, const int ID) : posX(posX), posY(posY), color(color), ID(ID) {
	fillRect = { posX * TILE_DIMENSION, posY* TILE_DIMENSION, TILE_DIMENSION, TILE_DIMENSION };
}

void Tile::draw(SDL_Renderer * gRenderer) const {
	SDL_SetRenderDrawColor( gRenderer, color.r, color.g, color.b, 0xFF );	
	SDL_RenderFillRect(gRenderer, &fillRect);
}

bool Tile::isWalkable() const { return false; }

bool Tile::isStartTile() const { return false;}

bool Tile::isAttackable() const { return false;}

void Tile::setTower(const std::shared_ptr<Tower> gameObject) {}

void Tile::unsetTower() {}

std::shared_ptr<Tower> Tile::getTower() const { throw std::string("Getting tower from incorrent tile."); }

int Tile::getX() const { return posX; }

int Tile::getY() const { return posY; }

int Tile::getID() const { return ID; }

