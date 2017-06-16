#ifndef __tile_h__
#define __tile_h__

#include <SDL2/SDL.h>
#include <memory>

class Tower;

/**
 * Class that represents the one tile of the map.
 * \throw std::string if the <b>getTower()</b> method is called from incorrect Tile. Check the subclasses for details.
 */
class Tile {

 public:
 	/**
 	 * Initialize member attributes.
 	 * \param posX Coordinate <b>X</b> of the tile.
 	 * \param posY Coordinate <b>Y</b> of the tile.
 	 * \param color Color of the tile.
 	 * \param ID ID of the tile.
 	 */
	Tile(int posX, int posY, const SDL_Color & color, const int ID);
	
	/** Draw the tile. */
	virtual void draw(SDL_Renderer * gRenderer) const;
	
	/** \return <b>TRUE</b> if the tile is walkable. Else <b>FALSE</b>. */
	virtual bool isWalkable() const;
	
	/** \return <b>TRUE</b> if the tile is starting tile. Else <b>FALSE</b>. */
	virtual bool isStartTile() const;
	
	/** \return <b>TRUE</b> if the tile is attackable. Else <b>FALSE</b>. */
	virtual bool isAttackable() const;
	
	/** Set the <b>tower</b> on tile*/
	virtual void setTower(const std::shared_ptr<Tower> tower);
	
	/** Unset the <b>tower</b> from tile*/
	virtual void unsetTower();
	
	/** \return Tower from tile */
	virtual std::shared_ptr<Tower> getTower() const;
	
	/** \return Coordinate <b>X</b> of tile (in the order of tile in the map) */
	int getX() const;
	
	/** \return Coordinate <b>Y</b> of tile (in the order of tile in the map) */
	int getY() const;
	
	/** \return ID of tile) */
	int getID() const;
 	static const int TILE_DIMENSION = 35; /**< A dimension(in pixels) of the one tile. */
 	
 protected:
	const int posX, posY;
	SDL_Color color;
	const int ID;
	SDL_Rect fillRect;
};

#endif /* __tile_h__ */
