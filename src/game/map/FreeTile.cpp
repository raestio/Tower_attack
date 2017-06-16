#include "FreeTile.h"
#include "../game_objects/Tower.h"
#include <iostream>
FreeTile::FreeTile(int posX, int posY, const int ID) : Tile(posX, posY, {RED, GREEN, BLUE}, ID) {}

bool FreeTile::isWalkable() const {
	if (!tower)	{ return true; }
	else { return false; }
}

bool FreeTile::isAttackable() const { return !isWalkable(); }

void FreeTile::setTower(const std::shared_ptr<Tower> tower) { this->tower = tower; }

void FreeTile::unsetTower() { tower.reset(); }

std::shared_ptr<Tower> FreeTile::getTower() const {	return tower; }
