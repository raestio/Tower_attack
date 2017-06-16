#include "GameObjectsLoader.h"
#include <SDL2/SDL.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../game_objects/GameObject.h"
#include "../game_objects/Tower.h"
#include "../game_objects/Attacker.h"
#include "../game_objects/abilities/Ability.h"
#include "../game_objects/abilities/BasicShot.h"
#include "../game_objects/abilities/ThreeAtTime.h"
#include "../game_objects/abilities/Freeze.h"


void GameObjectsLoader::loadGameObjects() {
	loadTowers();
	loadAttackers();
}

std::vector< std::shared_ptr<Tower> > GameObjectsLoader::getTowers() const { return towers; }

std::vector< std::shared_ptr<Attacker> > GameObjectsLoader::getAttackers() const { return attackers; }

void GameObjectsLoader::loadTowers() {
	std::ifstream towersDefFile(TOWERS_FILE_PATH);
	if(!towersDefFile) { throw std::string("Unable to load: " + std::string(TOWERS_FILE_PATH)); }
	
	std::string line, abilityStr;
	int red, green, blue, health, damage, range;
	double shootingSpeed;
	
    while (std::getline(towersDefFile, line)) {
    	std::vector< std::shared_ptr<Ability> > abilities;
        std::istringstream iss(line);
        
        iss >> red >> green >> blue >> health >> damage >> range >> shootingSpeed;
        if (!iss.good()) { throw std::string("A bad definition format in: " + std::string(TOWERS_FILE_PATH)); }
        
        while (iss >> abilityStr) abilities.push_back(std::shared_ptr<Ability> (getAbility(abilityStr, shootingSpeed, damage))); 
        if (abilities.empty()) { throw std::string("Some tower has no abilities in definition file."); }
     	
     	SDL_Color color = { red, green, blue };
     	towers.push_back(std::shared_ptr<Tower> (new Tower(color, health, damage, range, shootingSpeed, abilities)));	     
    } 
    
    towersDefFile.close();
}

Ability * GameObjectsLoader::getAbility(const std::string & abilityStr, double shootingSpeed, int damage) {
	if (abilityStr == "BASIC") { return new BasicShot(shootingSpeed, damage); }
	if (abilityStr == "FREEZE") { return new Freeze(shootingSpeed); }
	if (abilityStr == "THREE_AT_TIME") { return new ThreeAtTime(shootingSpeed, damage); }
	else { throw std::string("Unknown ability: " + abilityStr); }
}


void GameObjectsLoader::loadAttackers() {
	std::ifstream attackersFile(ATTACKERS_FILE_PATH);
	if(!attackersFile) { throw std::string("Unable to load: " + std::string(ATTACKERS_FILE_PATH)); }
	
	std::string line, name;
	int red, green, blue, health, damage, range;
	double shootingSpeed;
	
    while (std::getline(attackersFile, line)) {
        std::istringstream iss(line);     
        iss >> name >> red >> green >> blue >> health >> damage >> range >> shootingSpeed;
        if (iss.fail()) { throw std::string("A bad definition format in: " + std::string(ATTACKERS_FILE_PATH)); }
        
        iss.get();
		if (!iss.eof()) { throw std::string("A bad definition format in: " + std::string(ATTACKERS_FILE_PATH)); }
        
     	SDL_Color color = { red, green, blue };
     	attackers.push_back(std::shared_ptr<Attacker> (new Attacker(color, health, damage, range, shootingSpeed, name)));	     
    }
     
    attackersFile.close();
}
