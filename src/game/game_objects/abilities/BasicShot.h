#ifndef __basic_shot_h__
#define __basic_shot_h__

#include "Ability.h"
#include <iostream>

/** Basic shot with damage. */
class BasicShot : public Ability {

 public:
 	BasicShot(double shootingSpeed, int damage);
 	virtual void handleCollision() override;
 	virtual BasicShot * clone() const; 	
 	virtual void serialize(std::ostream & os) const override;
 	static const int RED = 0x00; /**< Red channel of the projectile color. */
 	static const int GREEN = 0x00; /**< Green channel of the projectile color. */
 	static const int BLUE = 0x00; /**< Blue channel of the projectile color. */
 private:
 	int damage;
};


#endif /* __basic_shot_h__ */
