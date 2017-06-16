#ifndef __attacker_h__
#define __attacker_h__

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "GameObject.h"

class Ability;

/** Attacker game object class */
class Attacker : public GameObject {

 public:
 	/** Initialize member attributes */
 	Attacker();
 	
 	/**Constructor initializes member attributes with given parameters. */
 	Attacker(const SDL_Color color, int health, int damage, int range, double shootingSpeed, const std::string & name);
 	
 	/** Copy constructor */
 	Attacker(const Attacker & x);
 	
 	/** Make a clone. */
 	virtual Attacker * clone() const;
 	
 	/** Update attacker. */
	virtual void update(double deltaTime) override;
	
	/** Draw attacker. */
 	virtual void draw(SDL_Renderer * gRenderer) const override;
 	
 	/**
 	 * Allow fire for the attacker.
 	 * \param target On which the attacker will shot. 
 	 */
 	virtual void allowFire(const std::shared_ptr<GameObject> target) override;
 	
 	/** Forbid fire for the attacker. */
 	virtual void forbidFire() override;
 	
 	/** \return <b>TRUE</b> if fire is allowed. Else <b>FALSE</b> */
 	virtual bool isFireAllowed() const override;
 	
 	/** Freeze attacker. */
 	virtual void freeze() override;
 	
 	/** \return Name of the attacker. */
 	std::string getName() const;
 	
 	/**
 	 * Set the path to attacker by which the attacker will be moving.
 	 * \param path Path for attacker.
 	 */
 	void setPath(const std::vector< std::pair<double, double> > & path);
 	
 	/** Move attacker */
 	void move(double deltaTime);
 	
 	/** Check if the attacker is touched with the point.
 	 * \param x \param y Coordinates of the point.
 	 * \return <b>TRUE</b> if is touched. Else <b>FALSE</b>
 	 */
 	bool isTouched(int x, int y) const;
 	
 	/** \return <b>TRUE</b> if the attacker is frozen. Else <b>FALSE</b> */
 	bool isFrozen() const;
 	
 	/** Unfreeze the attacker */
 	void unfreeze();
 	
 	virtual void serialize(std::ostream & os) const override;
 	virtual void deserialize(std::istream & is) override;
 	
 	const int MOVEMENT = 40; /**< Movement speed of the attacker. */
 	
 private:
 	/** Update directional vector */
 	void updateDirection();
 	
 	/** Update the target index in the <b>path</b> for attacker's move. */
 	void pathTargetIndexUpdate();
 	
 	/** Fix position for smooth attacker's move. */
 	void fixPosition();
 	
 	/** Update attacker's position */
 	void updatePosition(double deltaTime);
 	
 	/** \return <b>TRUE</b> if attacker moves to the left. Else <b>FALSE</b>. */
 	bool isMovingLeft() const;
 	
 	/** \return <b>TRUE</b> if attacker moves down. Else <b>FALSE</b>. */
 	bool isMovingDown() const;
 	
 	bool frozen;
 	std::string name;
 	int pathTargetIndex, radius;
 	int directionX; /**< X coordinate of directional vector for attacker's move.*/
 	int directionY; /**< Y coordinate of directional vector for attacker's move.*/
 	double shootingSpeed;
 	std::vector< std::pair<double, double> > path;
 	std::shared_ptr<Ability> ability;
};

#endif /* __attacker_h__ */
