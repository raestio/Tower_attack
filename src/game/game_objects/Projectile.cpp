#include "Projectile.h"
#include "../map/Tile.h"
#include <cmath>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <iostream>
#include "../TowerAttack.h"

Projectile::Projectile(double startX, double startY, std::weak_ptr<GameObject> target, const SDL_Color & color) : GameObject(color, 0, damage, 1, Tile::TILE_DIMENSION / 2), radius(width / 3), target(target) {
	targetCollision = false;
	posX = startX;
	posY = startY;
	double targetRenderX = target.lock()->getX() + target.lock()->getWidth() / 2;
	double targetRenderY = target.lock()->getY() + target.lock()->getWidth() / 2;
	double vectorSize = GameObject::pythagorean(targetRenderX - posX, targetRenderY - posY);

	directionX = (targetRenderX - posX) / vectorSize;
	directionY = (targetRenderY - posY) / vectorSize;
} 

Projectile * Projectile::clone() const { return new Projectile(*this); };

void Projectile::update(double deltaTime) {
	if (isTargetCollision()) {
		targetCollision = true;
		destroyed = true;
	}
	
	if (isOutOfMap()) { destroyed = true; }
	
	posX += deltaTime * directionX  * PROJECTILE_SPEED;
	posY += deltaTime * directionY * PROJECTILE_SPEED;
}

void Projectile::draw(SDL_Renderer * gRenderer) const {	filledCircleRGBA(gRenderer, posX, posY, radius, color.r, color.g, color.b, 0xFF); }
bool Projectile::hasCollidedWithTarget() const { return targetCollision; }

bool Projectile::isTargetCollision() const {
	auto targetPtr = target.lock();
	if (!targetPtr) { return true; }
	
	//Check collision
	if (posX + radius >= targetPtr->getX() 
		&& posY + radius >= targetPtr->getY() 
		&& posX + radius <= targetPtr->getX() + targetPtr->getWidth() 
		&& posY + radius <= targetPtr->getY() + targetPtr->getWidth()) {
		return true;
	}
	return false;
}

bool Projectile::isOutOfMap() const {
	if (posX + radius < 0 || posY + radius < 0 || posX + radius > TowerAttack::SCREEN_WIDTH || posY + radius > TowerAttack::SCREEN_HEIGHT) {
		return true;
	}
	return false;	
}
