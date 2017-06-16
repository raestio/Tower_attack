#include "Map.h"
#include "FinishTile.h"
#include "StartTile.h"
#include "WallTile.h"
#include "FreeTile.h"
#include "../game_objects/Tower.h"
#include <string>
#include <cmath>

Map::Map(const std::string & filePath) {
	load(filePath);
	this->filePath = filePath;
}

void Map::load(const std::string & filePath) {
	std::ifstream fileMap(filePath);
	this->filePath = filePath;
	if(!fileMap) { throw std::string("Unable to load map file."); }
	
	char tileChar;
	int ID = 1;
	for (int j = 0; j < MAP_HEIGHT; ++j) {
		
		std::vector<std::shared_ptr<Tile>> temp;
		for (int i = 0; i < MAP_WIDTH; ++i) {
			fileMap.get(tileChar);
			if (tileChar == NEW_LINE) fileMap.get(tileChar);
				
			switch (tileChar) {
				case WALL : temp.push_back(std::shared_ptr<Tile> (new WallTile(i, j, ID)));
					break;
				case FREE : temp.push_back(std::shared_ptr<Tile> (new FreeTile(i, j, ID)));
					break;
				case START : temp.push_back(std::shared_ptr<Tile> (new StartTile(i, j, ID)));
					break;
				case FINISH :
					finishTile = std::shared_ptr<Tile> (new FinishTile(i, j, ID));
					temp.push_back(finishTile);
					break;
				default : throw std::string("An incorrect map format.");
			}		
			++ID;
		}
		
		tileMap.push_back(temp);
	}
	
	fileMap.get();
	fileMap.get();
	if (!fileMap.eof()) { throw std::string("An incorrect map format."); }
	
	fileMap.close();
}

void Map::draw(SDL_Renderer * gRenderer) const {
	for (int j = 0; j < MAP_HEIGHT; ++j) {
		for (int i = 0; i < MAP_WIDTH; ++i) {
			tileMap[j][i]->draw(gRenderer);		
		}
	}
}

bool Map::isWalkableAt(int row, int col) const { return tileMap[row][col]->isWalkable(); }

bool Map::isStartTileAt(int x, int y) const { return tileMap[y / Tile::TILE_DIMENSION][x / Tile::TILE_DIMENSION]->isStartTile(); }

bool Map::isAttackableAt(int x, int y) const { return tileMap[y / Tile::TILE_DIMENSION][x / Tile::TILE_DIMENSION]->isAttackable(); }

std::shared_ptr<Tile> Map::getTileFrom(int x, int y) const { return tileMap[y / Tile::TILE_DIMENSION][x / Tile::TILE_DIMENSION]; }

void Map::deployTower(int row, int col, const std::shared_ptr<Tower> tower) { tileMap[row][col]->setTower(tower); }

std::shared_ptr<Tile> Map::getFinishTile() const { return finishTile; }

std::ostream & operator << (std::ostream & os, const Map & map) {
	os << map.filePath;
	return os;
}


















 
