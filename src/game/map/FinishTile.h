#ifndef __finish_tile_h__
#define __finish_tile_h__

#include "Tile.h"

/** Tile which is walkable and can not contain Tower object. It is the finish tile of the map. */
class FinishTile : public Tile {

 public:
	FinishTile(int posX, int posY, const int ID);
	virtual bool isWalkable() const override;
	static const int RED = 0x7E; /**< Red channel of the tile color. */
 	static const int GREEN = 0xFF; /**< Green channel of the tile color. */
 	static const int BLUE = 0x75; /**< Blue channel of the tile color. */
};

#endif /* __finish_tile_h__ */
