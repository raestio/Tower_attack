#include "Ability.h"
#include "../GameObject.h"


Ability::Ability(double shootingSpeed, const SDL_Color & projectileColor) : shootingSpeed(shootingSpeed), projectileColor(projectileColor) {
	timeToFire = shootingSpeed;
	isForbidden = true;
	setToBeForbidden = false;
}

void Ability::update(double posX, double posY, double deltaTime) {
	timeToFire += deltaTime;
	if (!isForbidden) {			
		this->handleProperty(posX, posY);		
		for (auto pIt = projectiles.begin(); pIt != projectiles.end(); ) {
			auto projectile = pIt;
			projectile->update(deltaTime);
			
			if (projectile->hasCollidedWithTarget() && target.lock()) { this->handleCollision(); }
			
			if (projectile->isDestroyed()) { pIt = projectiles.erase(pIt); }
			else ++pIt;
		}
		
		if (projectiles.empty() && setToBeForbidden) { isForbidden = true; }
	}		
}

void Ability::draw(SDL_Renderer * gRenderer) const {
	if (!isForbidden) {
		for (const auto & projectile : projectiles) {
			projectile.draw(gRenderer);
		}
	}
}

void Ability::handleProperty(double posX, double posY) {
	if (!setToBeForbidden && timeToFire >= shootingSpeed) {
		projectiles.push_back(Projectile(posX, posY, target, projectileColor));
		timeToFire = 0;		
	}		
}

void Ability::useOn(const std::shared_ptr<GameObject> target) {
	isForbidden = false;
	setToBeForbidden = false;
	this->target = target;
}

std::weak_ptr<GameObject> Ability::getTarget() const { return target; }

bool Ability::isAbilityForbidden() const { return isForbidden; }

void Ability::forbid() { setToBeForbidden = true; }

std::ostream & operator << (std::ostream & os, const Ability & a) {
	a.serialize(os);
	return os;
}
