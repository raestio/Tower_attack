#ifndef __wall_tile_h__
#define __wall_tile_h__

#include "Tile.h"

/** Tile which is not walkable and can not contain Tower object. */
class WallTile : public Tile {

 public:
	WallTile(int posX, int posY, const int ID);
	static const int RED = 0x70; /**< Red channel of the tile color. */
 	static const int GREEN = 0x70; /**< Green channel of the tile color. */
 	static const int BLUE = 0x70; /**< Blue channel of the tile color. */
};

#endif /* __wall_tile_h__ */
