#ifndef __free_tile_h__
#define __free_tile_h__

#include <memory>
#include "Tile.h"

class Tower;

/** Tile which is walkable and can contain Tower object. */
class FreeTile : public Tile {

 public:
	FreeTile(int posX, int posY, const int ID);
	virtual bool isWalkable() const override;
	virtual bool isAttackable() const override;
 	virtual void setTower(const std::shared_ptr<Tower> tower) override;
 	virtual void unsetTower() override;
 	virtual std::shared_ptr<Tower> getTower() const override;
 	static const int RED = 0xEC; /**< Red channel of the tile color. */
 	static const int GREEN = 0xC9; /**< Green channel of the tile color. */
 	static const int BLUE = 0x82; /**< Blue channel of the tile color. */
 private:
 	std::shared_ptr<Tower> tower;
};

#endif /* __free_tile_h__ */
