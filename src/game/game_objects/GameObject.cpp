#include "GameObject.h"
#include <iostream>
#include <cmath>
#include <SDL2/SDL2_gfxPrimitives.h>

GameObject::GameObject() {
	color = {0, 0, 0, 0};
	destroyed = false;
	maxHealth = health = damage = range = width = posX = posY = 0;
}

GameObject::GameObject(const SDL_Color color, int health, int damage, int range, int width) :
	color(color), health(health), damage(damage), range(range), width(width) {
	maxHealth = health;
	destroyed = false;
}

GameObject::~GameObject() {}

void GameObject::update(double deltaTime) {
	if (health <= 0) { destroyed = true; }
}

void GameObject::setPosition(double x, double y) {
	posX = x;
	posY = y;
}

void GameObject::allowFire(const std::shared_ptr<GameObject> target) {};

void GameObject::forbidFire() {};

bool GameObject::isFireAllowed() const { return false; };

void GameObject::serialize(std::ostream & os) const {
	os << (int)color.r << " " << (int)color.g << " " << (int)color.b << " " << (int)color.a << " " 
		<< destroyed << " "	<< maxHealth << " " << health << " " << damage << " " << range << " " 
		<< width << " " << posX << " " << posY << " ";
}

void GameObject::deserialize(std::istream & is) {
	int r, g, b, a;
	r = g = b = a = 0;
	is >> r >> g >> b >> a >> destroyed >> maxHealth >> health >> damage >> range >> width >> posX >> posY;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}

void GameObject::freeze() {};

double GameObject::getX() const { return posX; }

double GameObject::getY() const { return posY; }

int GameObject::getWidth() const { return width; }

bool GameObject::isDestroyed() const { return destroyed; }

void GameObject::decreaseHealth(int hp) { health -= hp; }

bool GameObject::isInRange(double x, double y, int width) const {
	if (isInRangeBetween(posX + width / 2, posY + width / 2, x + width, y + width)
		|| isInRangeBetween(posX + width / 2, posY + width / 2, x, y)
		|| isInRangeBetween(posX + width / 2, posY + width / 2, x, y + width)
		|| isInRangeBetween(posX + width / 2, posY + width / 2, x + width, y)
	   ) return true;	
	
	return false;
}

std::ostream & operator << (std::ostream & os, const GameObject & o) {
	o.serialize(os);
	return os;
}

std::istream & operator >> (std::istream & is, GameObject & o) {
	o.deserialize(is);
	return is;
}

void GameObject::copyAttributes(const GameObject & x) {
	color = x.color;
	destroyed = x.destroyed;
	maxHealth = x.maxHealth;
	health = x.health;
	damage = x.damage;
	range = x.range;
	width = x.width;
	posX = x.posX;
	posY = x.posY;
}

void GameObject::drawHealth(SDL_Renderer * gRenderer) const {
	int red = 0xFF0000FF;
	double hWidth = 2*width / 3;
	double hPosX = posX + hWidth / 4;
	double hPosY = posY + hWidth / 4;
	boxRGBA(gRenderer,  hPosX, hPosY, hPosX + hWidth, hPosY + hWidth, 0x00, 0xFF, 0x00, 0xFF);
	double croppedSize = (hWidth / maxHealth) * (maxHealth - health);
	if (croppedSize != 0) { 
		boxColor(gRenderer, hPosX, hPosY, hPosX + hWidth, hPosY + croppedSize, red);
	} 
}

bool GameObject::isInRangeBetween(double x1, double y1, double x2, double y2) const {
	return pythagorean(x1 - x2, y1 - y2) < range * Tile::TILE_DIMENSION;
}

double GameObject::pythagorean(double a, double b) const { return sqrt(a * a + b * b); }




