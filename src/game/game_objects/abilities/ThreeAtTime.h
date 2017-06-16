#ifndef __three_at_time_h__
#define __three_at_time_h__

#include "Ability.h"
#include "../../tools/Timer.h"
#include <iostream>

/** Three at a time shot with damage. */
class ThreeAtTime : public Ability {

 public:
	ThreeAtTime(double shootingSpeed, int damage);
	virtual void handleCollision() override;
	virtual void handleProperty(double posX, double posY) override;
	virtual ThreeAtTime * clone() const;
	virtual void serialize(std::ostream & os) const override;
	static constexpr double PROJECTILES_DELAY = 0.08; /**< Delay between shots */
 	static const int PROJECTILES_FINAL_COUNT = 3; /**< Number of shots at a time */
	static const int RED = 0xFF; /**< Red channel of the projectile color. */
 	static const int GREEN = 0x00; /**< Green channel of the projectile color. */
 	static const int BLUE = 0x00; /**< Blue channel of the projectile color. */
 private:
 	int damage, projectilesCount;
 	Timer projectilesTimer;
};

#endif /* __freeze_h */
