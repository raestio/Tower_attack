#include "BasicShot.h"
#include "../Projectile.h"

BasicShot::BasicShot(double shootingSpeed, int damage) : Ability(shootingSpeed, { RED, GREEN, BLUE }), damage(damage) {}

BasicShot * BasicShot::clone() const { return new BasicShot(*this); }

void BasicShot::handleCollision() { target.lock()->decreaseHealth(damage); }

void BasicShot::serialize(std::ostream & os) const { os << "BASIC"; }
