#include "Attacker.h"
#include <iostream>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <cmath>
#include "../map/Tile.h"

#include "abilities/BasicShot.h"

Attacker::Attacker() : GameObject() {
	name = "";
	frozen = false;
	pathTargetIndex = directionX = directionY = radius = shootingSpeed = 0;
	ability = std::shared_ptr<Ability> (new BasicShot(shootingSpeed, damage));
}

Attacker::Attacker(const SDL_Color color, int health, int damage, int range, double shootingSpeed, const std::string & name) : 
				GameObject(color, health, damage, range, Tile::TILE_DIMENSION), shootingSpeed(shootingSpeed), name(name), frozen(false) {
	pathTargetIndex = 0;
	directionX = -1;
	directionY = 0;
	radius = width / 2; 
	ability = std::shared_ptr<Ability> (new BasicShot(shootingSpeed, damage));
}

Attacker::Attacker(const Attacker & x) {
	GameObject::copyAttributes(x);
	frozen = x.frozen;
	name = x.name;
	pathTargetIndex = x.pathTargetIndex;
	directionX = x.directionX;
	directionY = x.directionY;
	radius = x.radius;
 	shootingSpeed = x.shootingSpeed;
 	path = x.path;
 	ability = std::shared_ptr<Ability> (x.ability->clone());
}

Attacker * Attacker::clone() const { return new Attacker(*this); }

void Attacker::update(double deltaTime) {
	GameObject::update(deltaTime);
	if (!frozen) { ability->update(posX + radius, posY + radius, deltaTime); }
}

void Attacker::draw(SDL_Renderer * gRenderer) const {
	filledCircleRGBA(gRenderer, posX + radius, posY + radius, radius,
					 color.r, color.g, color.b, 0xFF);
	drawHealth(gRenderer);
	if (frozen) {
		filledCircleRGBA(gRenderer, posX + radius, posY + radius, radius, 
					 	 0x00, 0xDE, 0xFF, 0x66);
	}
	ability->draw(gRenderer);	
}

void Attacker::allowFire(const std::shared_ptr<GameObject> target) { ability->useOn(target); }

void Attacker::forbidFire() { ability->forbid(); }
 
bool Attacker::isFireAllowed() const { return !ability->isAbilityForbidden(); }

void Attacker::freeze() { frozen = true; }

std::string Attacker::getName() const { return name; }

void Attacker::setPath(const std::vector< std::pair<double, double> > & path) { this->path = path; }

void Attacker::move(double deltaTime) {
	if (pathTargetIndex < path.size() - 1) { pathTargetIndexUpdate(); }
	updatePosition(deltaTime);
}

bool Attacker::isTouched(int x, int y) const {
	if (GameObject::pythagorean(x - (posX + radius), y - (posY + radius)) <= radius) { return true;	}
	else { return false; }
}

bool Attacker::isFrozen() const { return frozen; }

void Attacker::unfreeze() {	frozen = false; }

void Attacker::serialize(std::ostream & os) const {
	GameObject::serialize(os);
	os << shootingSpeed << " " << name << " " << pathTargetIndex << " " << directionX << " " << directionY << " " << radius << " ";
	for (auto pathPart : path) { 
		os << pathPart.first << " " << pathPart.second << " ";
	}
	os << -99;
}

void Attacker::deserialize(std::istream & is) {
	GameObject::deserialize(is);
	is >> shootingSpeed >> name >> pathTargetIndex >> directionX >> directionY >> radius;

	int x, y;
	x = y = 0;
	while (true) {
		is >> x;
		if (x == -99) { break; }
		is >> y;	
		path.push_back(std::pair<double, double>(x, y));
	}
	
	ability = std::shared_ptr<Ability> (new BasicShot(shootingSpeed, damage));
}

void Attacker::updateDirection() {
	if (posX  == path[pathTargetIndex].first) { directionX = 0; }
	else if (posX > path[pathTargetIndex].first) { directionX = -1; }
	else { directionX = 1; }
	
	if (posY == path[pathTargetIndex].second) { directionY = 0; } 
	else if (posY > path[pathTargetIndex].second) { directionY = -1; } 
	else { directionY = 1; }
	
}

void Attacker::pathTargetIndexUpdate() {
	fixPosition();		
	if (posY == path[pathTargetIndex].second && posX == path[pathTargetIndex].first) {
		++pathTargetIndex;
		updateDirection();	
	}
}
			
void Attacker::fixPosition() {
	if (isMovingLeft() && posX < path[pathTargetIndex].first) {	posX = path[pathTargetIndex].first;	} 
	else if (!isMovingLeft() && posX > path[pathTargetIndex].first) { posX = path[pathTargetIndex].first; }
	
	if (!isMovingDown() && posY < path[pathTargetIndex].second) { posY = path[pathTargetIndex].second; } 
	else if (isMovingDown() && posY > path[pathTargetIndex].second) { posY = path[pathTargetIndex].second; }
}

void Attacker::updatePosition(double deltaTime) {
	posX += MOVEMENT * deltaTime * directionX;
	posY += MOVEMENT * deltaTime * directionY;
}

bool Attacker::isMovingLeft() const { return directionX == -1; }

bool Attacker::isMovingDown() const { return directionY == 1; }
