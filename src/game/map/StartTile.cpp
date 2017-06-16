#include "StartTile.h"

StartTile::StartTile(int posX, int posY, const int ID) : Tile(posX, posY, {RED, GREEN, BLUE}, ID) {}

bool StartTile::isWalkable() const { return true; }

bool StartTile::isStartTile() const { return true; }
