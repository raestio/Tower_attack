#include "FinishTile.h"

FinishTile::FinishTile(int posX, int posY, const int ID) : Tile(posX, posY, {RED, GREEN, BLUE}, ID) {}

bool FinishTile::isWalkable() const { return true; }
