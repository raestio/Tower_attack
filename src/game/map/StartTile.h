#ifndef __start_tile_h__
#define __start_tile_h__

#include "Tile.h"

/** Tile which is walkable and can not contain Tower object. It is the starting tile of the map. */
class StartTile : public Tile {

 public:
	StartTile(int posX, int posY, const int ID);
	virtual bool isWalkable() const override;
	virtual bool isStartTile() const override;
	static const int RED = 0x64; /**< Red channel of the tile color. */
 	static const int GREEN = 0xD6; /**< Green channel of the tile color. */
 	static const int BLUE = 0xFF; /**< Blue channel of the tile color. */
};

#endif /* __start_tile_h__ */
