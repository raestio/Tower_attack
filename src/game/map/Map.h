#ifndef __map_h__
#define __map_h__

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include "Tile.h"
#include "../TowerAttack.h"
#include <memory>
#include <vector>

class Tower;

/** Class that represents the map of the game. 
 * \throw std::string description of error which can be caused by loading or reading from the map file. 
 */
class Map {

 public:
 	
 	/** Loads the map from the file.
	 * \param filePath - path to the file.
	 */
 	Map(const std::string & filePath);
	
	/** Load the map from the file.
	 * \param filePath - path to the file.
	 */
	void load(const std::string & filePath);	
	
	/** Draw the map to the screen. */
	void draw(SDL_Renderer * gRenderer) const;
	
	/** \return <b>TRUE</b> if the tile at <b>[row, col]</b> is walkable. Else <b>FALSE</b>. */
	bool isWalkableAt(int row, int col) const;
	
	/** \return <b>TRUE</b> if the tile at position <b>x, y</b> is starting tile. Else <b>FALSE</b>. */
	bool isStartTileAt(int x, int y) const;
	
	/** \return <b>TRUE</b> if the tile at position <b>x, y</b> is attackable. Else <b>FALSE</b>. */
	bool isAttackableAt(int x, int y) const;
	
	/** \return Tile from the position <b>x, y</b>. */
	std::shared_ptr<Tile> getTileFrom(int x, int y) const;
	
	/** Deploy <b>tower</b> on the map at <b>[row, col]</b> */
	void deployTower(int row, int col, const std::shared_ptr<Tower> tower);
	
	/** \return Finish tile of the map. */
	std::shared_ptr<Tile> getFinishTile() const;
	
	/** Overloaded operator to serialize the map. */
	friend std::ostream & operator << (std::ostream & os, const Map & map);
	
	static const int MAP_WIDTH = TowerAttack::SCREEN_WIDTH / Tile::TILE_DIMENSION; /** Width of the map (number of tiles) */
	static const int MAP_HEIGHT = TowerAttack::SCREEN_HEIGHT / Tile::TILE_DIMENSION; /** Height of the map (number of tiles) */
	
 private:
	static const char WALL = '#'; 
	static const char FREE = ' ';
	static const char START = '>';
	static const char FINISH = '<';
	static const char NEW_LINE = '\n';
	std::string filePath;
	std::shared_ptr<Tile> finishTile;
	std::vector< std::vector< std::shared_ptr<Tile> > > tileMap;
};

#endif /* __map_h__ */
