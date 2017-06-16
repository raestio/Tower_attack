#ifndef __ability_h__
#define __ability_h__

#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "../Projectile.h"
#include <iostream>
class GameObject;

/**
 * Abstract class that represents the ability of the game objects. 
 * Manages the behaviour between projectiles and game objects.
 */
class Ability {
	
 public:
 	/** Initialize member attributes. */
 	Ability(double shootingSpeed, const SDL_Color & projectileColor);
 	
 	/** Make clone */
 	virtual Ability * clone() const = 0;
 	
 	/** Update ability.
 	 * \param posX Coordinate <b>X</b> of the GameObject.
 	 * \param posY Coordinate <b>Y</b> of the GameObject.
 	 * \param deltaTime
 	 */
 	virtual void update(double posX, double posY, double deltaTime);
 	
 	/**
 	 * Draw projectiles of ability.
 	 */
 	virtual void draw(SDL_Renderer * gRenderer) const;
 	
 	/**
 	 * Handle collision between Projectile and GameObject.
 	 */
 	virtual void handleCollision() = 0;
 	
 	/** Handle the property of ability */
 	virtual void handleProperty(double posX, double posY);
	
	/** Use ability against another game object.
	 * \param target 
	 */
	void useOn(const std::shared_ptr<GameObject> target);
	
	/** \return Target of the ability (projectiles). */
	std::weak_ptr<GameObject> getTarget() const;
	
	/** \return <b>TRUE</b> if ability is forbidden. Else <b>FALSE</b> */
	bool isAbilityForbidden() const;
	
	/** Forbid ability. */
	void forbid();
	
	/** Serialize ability. */
	virtual void serialize(std::ostream & os) const = 0;
	
	/** Overloaded operator for the serialization. */
	friend std::ostream & operator << (std::ostream & os, const Ability & a);
	
 protected:
 	double shootingSpeed;
 	std::vector< Projectile > projectiles;
 	std::weak_ptr<GameObject> target;
 	double timeToFire;
 	SDL_Color projectileColor;
 	bool isForbidden, setToBeForbidden;
};

#endif /* __ability_h__ */
