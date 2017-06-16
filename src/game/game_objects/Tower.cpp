#include "Tower.h"
#include <iostream>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "abilities/Ability.h"
#include "abilities/BasicShot.h"
#include "abilities/Freeze.h"
#include "abilities/ThreeAtTime.h"

Tower::Tower() : GameObject() {	shootingSpeed = 0; }

Tower::Tower(const SDL_Color color, int health, int damage, int range, double shootingSpeed, const std::vector<std::shared_ptr<Ability>> & abilities) : 
				GameObject(color, health, damage, range, Tile::TILE_DIMENSION), shootingSpeed(shootingSpeed), abilities(abilities), abilityNumber(0) {}
	
Tower::Tower(const Tower & x) {
	GameObject::copyAttributes(x);
	shootingSpeed = x.shootingSpeed;
	abilityNumber = x.abilityNumber;
	for (auto ability : x.abilities) {
		abilities.push_back(std::shared_ptr<Ability> (ability->clone()));
	}
}	
				
Tower * Tower::clone() const { return new Tower(*this); }

void Tower::update(double deltaTime) {
	GameObject::update(deltaTime);
	abilities[abilityNumber]->update(posX + width / 2, posY + width / 2, deltaTime);
}

void Tower::draw(SDL_Renderer * gRenderer) const {
	roundedBoxRGBA(gRenderer, posX, posY, posX + width, posY + width, 6, color.r, color.g, color.b, 0xFF);
	drawHealth(gRenderer);
	abilities[abilityNumber]->draw(gRenderer);
}

void Tower::allowFire(const std::shared_ptr<GameObject> target) {
	abilityNumber = rand() % abilities.size();
	abilities[abilityNumber]->useOn(target);
} 

void Tower::forbidFire() { abilities[abilityNumber]->forbid(); } 
void Tower::setPosition(double x, double y) { GameObject::setPosition(x * width, y * width); }
bool Tower::isFireAllowed() const {	return !abilities[abilityNumber]->isAbilityForbidden(); }

bool Tower::isStillInRange() const {
	if (!abilities[abilityNumber]->isAbilityForbidden()) {
		std::shared_ptr<GameObject> target = abilities[abilityNumber]->getTarget().lock();
		if (!target) return false;
		return isInRange(target->getX(), target->getY(), target->getWidth()) && !target->isDestroyed();
	} 
	return false;
}

void Tower::serialize(std::ostream & os) const {
	GameObject::serialize(os);
	os << shootingSpeed << " " << abilityNumber << " ";
	for (auto ability : abilities) { 
		os << *ability << " "; 
	}
	os << "$$$";
}

void Tower::deserialize(std::istream & is) {
	GameObject::deserialize(is);
	is >> shootingSpeed >> abilityNumber;
	std::string ability;
	while (true) {
		is >> ability;
		if (ability == "BASIC") { abilities.push_back(std::shared_ptr<Ability> (new BasicShot(shootingSpeed, damage))); }
		else if (ability == "FREEZE") { abilities.push_back(std::shared_ptr<Ability> (new Freeze(shootingSpeed))); }
		else if (ability == "THREE_AT_TIME") { abilities.push_back(std::shared_ptr<Ability> (new ThreeAtTime(shootingSpeed, damage))); }
		else { return; }
	}
}

