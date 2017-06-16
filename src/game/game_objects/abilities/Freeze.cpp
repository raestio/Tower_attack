#include "Freeze.h"
#include "../Projectile.h"

Freeze::Freeze(double shootingSpeed) : Ability(shootingSpeed, { RED, GREEN, BLUE }) {}

Freeze * Freeze::clone() const { return new Freeze(*this); }

void Freeze::handleCollision() { target.lock()->freeze(); }

void Freeze::serialize(std::ostream & os) const { os << "FREEZE"; }
