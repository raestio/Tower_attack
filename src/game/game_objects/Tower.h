#ifndef __tower_h__
#define __tower_h__

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "GameObject.h"
class Ability;

/** Tower game object class */
class Tower : public GameObject {

 public:
 	/** Initialize member attributes. */
 	Tower();
 	
 	/** Constructor initializes member attributes with given parameters. */
 	Tower(const SDL_Color color, int health, int damage, int range, double shootingSpeed, const std::vector<std::shared_ptr<Ability>> & abilities);
 	
 	/** Copy constructor. */
 	Tower(const Tower & x);
 	
 	/** Make a clone. */
 	virtual Tower * clone() const;
 	
 	/** Update tower. */
	virtual void update(double deltaTime) override;
	
	/** Draw tower. */
 	virtual void draw(SDL_Renderer * gRenderer) const override;
 	
 	/** Set the position of tower. */
 	virtual void setPosition(double x, double y) override;
 	
	/**
 	 * Allow fire for the tower.
 	 * \param target On which the tower will shot. 
 	 */
 	virtual void allowFire(const std::shared_ptr<GameObject> target) override;
 	
 	/** Forbid fire for the tower. */
 	virtual void forbidFire() override;
 		
 	/** \return <b>TRUE</b> if fire is allowed. Else <b>FALSE</b> */
 	virtual bool isFireAllowed() const override;
 	
 	/** Check if tower has still in range its target. 
 	 * \return <b>TRUE</b> if has. Else <b>FALSE</b>.
 	 */
 	bool isStillInRange() const;
 	
 	virtual void serialize(std::ostream & os) const override;
 	virtual void deserialize(std::istream & is) override;
 	
 private:
 	double shootingSpeed;
 	int abilityNumber; /**< Index of allowed tower's ability in <b>abilities</b>. */
 	std::vector< std::shared_ptr<Ability> > abilities;
};

#endif /* __tower_h__ */
