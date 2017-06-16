#include "GameManager.h"

#include "../map/Map.h"
#include "../game_objects/Tower.h"
#include "../game_objects/Attacker.h"
#include "../game_objects/GameObject.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>

void GameManager::saveGame(const std::shared_ptr<Map> map,
 						   const std::vector< std::shared_ptr<Tower> > & towers, const std::vector< std::shared_ptr<Attacker> > & attackers,
						   const Timer & freezeTimer,
						   bool attackersAttacking, bool attackersFrozen,
						   int score) {
						
	
	serializeObject(*map, SAVE_OBJECTS_PATH, false);
	serializeObject(freezeTimer, SAVE_OBJECTS_PATH, true);
	serializeObject(attackersAttacking, SAVE_OBJECTS_PATH, true);
	serializeObject(attackersFrozen, SAVE_OBJECTS_PATH, true);
	serializeObject(score, SAVE_OBJECTS_PATH, true);
	
	serializeVector(towers, SAVE_TOWERS_PATH);
	serializeVector(attackers, SAVE_ATTACKERS_PATH);					
}

template<typename Object> 
void GameManager::serializeObject(const Object & obj, const char * filePath, bool append) {
	std::ofstream fileObject;
	if (append) fileObject.open(filePath, std::fstream::app);
	else fileObject.open(filePath);	
	if (!fileObject) throw std::string("Can not write to file: " + std::string(filePath));
	
	fileObject << obj << std::endl;
	fileObject.close();
}

template<typename Container> 
void GameManager::serializeVector(const Container & objects, const char * filePath) {
	int i = 0;
	for (auto objPtr : objects) {
		if (i == 0) serializeObject(*objPtr, filePath, false);
		else serializeObject(*objPtr, filePath, true);
		i++;
	}
}

void GameManager::loadGame(std::shared_ptr<Map> * map,
 						   std::vector< std::shared_ptr<Tower> > & towers, std::vector< std::shared_ptr<Attacker> > & attackers,
 						   Timer & freezeTimer,
 						   bool & attackersAttacking, bool & attackersFrozen,
 						   int & score) {
						
	std::string mapPath;
	deserializeObject(mapPath, SAVE_OBJECTS_PATH, 1);
	*map = std::shared_ptr<Map> (new Map(mapPath));
	
	deserializeObject(freezeTimer, SAVE_OBJECTS_PATH, 2);
	deserializeObject(attackersAttacking, SAVE_OBJECTS_PATH, 3);
	deserializeObject(attackersFrozen, SAVE_OBJECTS_PATH, 4);
	deserializeObject(score, SAVE_OBJECTS_PATH, 5);
	
	for (int i = 1; ; i++) {
		Tower tempTower;
		if (!deserializeObject(tempTower, SAVE_TOWERS_PATH, i)) { break; }
		
		towers.push_back(std::shared_ptr<Tower> (new Tower(tempTower)));
		auto tower = towers.back();
		(*map)->deployTower(tower->getY() / Tile::TILE_DIMENSION, tower->getX() / Tile::TILE_DIMENSION, tower);
	}
	
	for (int i = 1; ; i++) {
		Attacker tempAtt;
		if (!deserializeObject(tempAtt, SAVE_ATTACKERS_PATH, i)) { break; }
		
		attackers.push_back(std::shared_ptr<Attacker> (new Attacker(tempAtt)));
	}
}

template<typename Object> 
bool GameManager::deserializeObject(Object & obj, const char * filePath, int line) {
	std::ifstream fileObject(filePath);
	if (!fileObject) { throw std::string("Unable to load file: " + std::string(filePath)); }
	
	goToLine(fileObject, line);	
	fileObject.get();	
	if (fileObject.eof()) { return false; }
	fileObject.unget();
	
	fileObject >> obj;

	fileObject.close();
	return true;
}

std::ifstream & GameManager::goToLine(std::ifstream & file, int line) {
	file.seekg(std::ios::beg);
    for(int i = 0; i < line - 1; ++i) {
    	file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}
