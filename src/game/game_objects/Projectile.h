#ifndef __projectile_h__
#define __projectile_h__

#include <memory>
#include "GameObject.h"

/** Projectile game object class */
class Projectile : public GameObject {

 public:
 	/**
 	 * Initialize member attributes.
 	 * \param startX Coordinate <b>X</b> where the projectile starts.
 	 * \param startY Coordinate <b>Y</b> where the projectile starts.
 	 * \param target Target of the projectile.
 	 * \param color Color of the projectile.
 	 */
 	Projectile(double startX, double startY, std::weak_ptr<GameObject> target, const SDL_Color & color);
	
	/** Make a clone. */
 	virtual Projectile * clone() const;
	
	/** Update projectile. \param deltaTime */
	virtual void update(double deltaTime) override;
	
	/** Draw projectile. \param gRenderer */
 	virtual void draw(SDL_Renderer * gRenderer) const override;
 	
	/** \return <b>TRUE</b> if the projectile collided with the target. Else <b>FALSE</b>. */
	bool hasCollidedWithTarget() const;
	
	static constexpr double PROJECTILE_SPEED = 230.0; /**< Speed of the projectile. */

 private:
 	/** 
 	 * Check the collision with the target.
 	 * If the target is destroyed before the projectile's hit. Returns <b>TRUE</b> and the projectile will be destroyed. 
 	 * \return <b>TRUE</b> if is collision with the target. Else <b>FALSE</b>. 
 	 */
 	bool isTargetCollision() const;
 	
 	/** \return <b>TRUE</b> if the projectile is out of the map. Else <b>FALSE</b>. */
 	bool isOutOfMap() const;
 	int radius;
 	double directionX, directionY;
 	bool targetCollision;
 	std::weak_ptr<GameObject> target;
};

#endif /* __projectile_h__ */
