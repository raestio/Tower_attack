#include "ThreeAtTime.h"

#include "../Projectile.h"

ThreeAtTime::ThreeAtTime(double shootingSpeed, int damage) : Ability(shootingSpeed, { RED, GREEN, BLUE }), damage(damage), projectilesCount(0) {}

ThreeAtTime * ThreeAtTime::clone() const { return new ThreeAtTime(*this); }

void ThreeAtTime::handleProperty(double posX, double posY) {
	if (!projectilesTimer.isStarted() && (!setToBeForbidden && timeToFire >= shootingSpeed)) {
		projectilesTimer.start(PROJECTILES_DELAY);
	}
	
	if ((!setToBeForbidden && timeToFire >= shootingSpeed) && projectilesTimer.finished()) {
		projectiles.push_back(Projectile(posX, posY, target, projectileColor));
		projectilesCount++;
		if (projectilesCount == PROJECTILES_FINAL_COUNT) {
			timeToFire = projectilesCount = 0;
		}		
	}	
}

void ThreeAtTime::handleCollision() { target.lock()->decreaseHealth(damage); }

void ThreeAtTime::serialize(std::ostream & os) const { os << "THREE_AT_TIME"; }
