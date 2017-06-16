#ifndef __freeze_h__
#define __freeze_h__

#include "Ability.h"

/** Shot that freezes game object. */
class Freeze : public Ability {

 public:
	Freeze(double shootingSpeed);
	virtual void handleCollision() override;
	virtual Freeze * clone() const;
	static constexpr double DURATION = 3.0; /**< Freeze time duration. */
	virtual void serialize(std::ostream & os) const override;
	static const int RED = 0x00; /**< Red channel of the projectile color. */
 	static const int GREEN = 0xDE; /**< Green channel of the projectile color. */
 	static const int BLUE = 0xFF; /**< Blue channel of the projectile color. */
};

#endif /* __freeze_h */
