#include "PlayState.h"
#include "GameStateManager.h"
#include "../TowerAttack.h"
#include "../map/Map.h"
#include "../map/Tile.h"
#include "../game_objects/GameObject.h"
#include "../game_objects/Attacker.h"
#include "../game_objects/Tower.h"
#include "../game_objects/abilities/Freeze.h"
#include "../tools/GameManager.h"
#include "GameOverState.h"
#include <iostream>
PlayState::PlayState(GameStateManager * gsm, const std::shared_ptr<Map> map, 
					 const std::vector< std::shared_ptr<Tower> > & deployedTowers, const std::vector< std::shared_ptr<Attacker> > & selectedAttackers,
					 const std::shared_ptr<Tile> startTile) : State(gsm), map(map), towers(deployedTowers), attackers(selectedAttackers), score(0) {
					 
	pathFinder.setNodeMap(map);
	pathFinder.findPath(startTile, map->getFinishTile());
	attackersAttacking = attackersFrozen  = false;
	int i = 0;
	for (auto & attacker : attackers) {
		attacker->setPosition(startTile->getX() * Tile::TILE_DIMENSION + i * Tile::TILE_DIMENSION, startTile->getY() * Tile::TILE_DIMENSION);
		attacker->setPath(pathFinder.getShortestPath());
		i++;
	}
}

PlayState::PlayState(GameStateManager * gsm, const std::shared_ptr<Map> map, 
					 const std::vector< std::shared_ptr<Tower> > & towers, const std::vector< std::shared_ptr<Attacker> > & attackers,
					 bool attackersAttacking, bool attackersFrozen,
					 const Timer & freezeTimer,	int score) : 
					 State(gsm), map(map), towers(towers), attackers(attackers), attackersAttacking(attackersAttacking), attackersFrozen(attackersFrozen), freezeTimer(freezeTimer), score(score) {
	
	if (attackersFrozen) { freezeAttackers(); }
}


void PlayState::inputHandle() {
	SDL_Event e;
	while( SDL_PollEvent( &e ) != 0 ) {
		switch (e.type) {
			case SDL_QUIT : 
				GameManager::saveGame(map, towers, attackers, freezeTimer, attackersAttacking, attackersFrozen, score);
				throw TowerAttack::QUIT_GAME;
				break;
			case SDL_MOUSEBUTTONDOWN : handleAttackers(e);
				break;
		}
	}
}

void PlayState::update(double deltaTime) {
	//Unfreeze attackers if the freeze timer has finished.
	if (freezeTimer.isStarted() && freezeTimer.finished()) {
		attackersFrozen = false;
		unfreezeAttackers();	
	}
	
	//Chceck if some of the attackers is frozen. If so, freeze all attackers.
	if (!attackersFrozen) {
		for (auto attacker : attackers) {
			if (attacker->isFrozen()) { 
				freezeAttackers();	
				attackersFrozen = true;
				freezeTimer.start(Freeze::DURATION);
				break; 
			}
		}
	}
	
	//Updating each attacker and checking if the attackers are alive.
	for (auto aIt = attackers.begin(); aIt != attackers.end(); ++aIt) {
		auto attacker = *aIt;	
		attacker->update(deltaTime);				
		if (attacker->isDestroyed()) {
			attackers.erase(aIt);		
			--aIt;
		}			
	}
	
	//Move each of the attackers if are not attacking nor frozen. 
	if (!attackersAttacking && !attackersFrozen) {
		for (auto attacker : attackers) {
			attacker->move(deltaTime);
		}
	}
	
	//Updating towers
	for (auto tIt = towers.begin(); tIt != towers.end(); ++tIt) {
		auto tower = *tIt;	
		
		//Deciding if the tower can shoot or not.
		if (!tower->isFireAllowed()) {
			findTargetForTower(tower);
		} else {
			if (!tower->isStillInRange()) {
				tower->forbidFire();
			}
		}
			
		tower->update(deltaTime);		
		
		//Checking if the tower is alive and incrementing the player's score
		if (tower->isDestroyed()) {
			score += 5;
			
			//Tower is destroyed, attackers are moving on and can not shoot.
			attackersAttacking = false;
			for (auto attacker : attackers) {
				attacker->forbidFire();
			}
			
			//Unset tower from the map
			map->getTileFrom(tower->getX(), tower->getY())->unsetTower();
			towers.erase(tIt);		
			--tIt;
		}			
	}
	
	checkGameStatus();	
}

void PlayState::render(SDL_Renderer * gRenderer) const {	
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( gRenderer );
		
	map->draw(gRenderer);

	for (auto attacker : attackers) {
		attacker->draw(gRenderer);
	}
	
	for (auto tower : towers) {
		tower->draw(gRenderer);
	}
	
	SDL_RenderPresent(gRenderer);
}

void PlayState::handleAttackers(SDL_Event & e) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	
	if (map->isAttackableAt(x, y)) {
		
		attackersAttacking = false;
		auto tower = map->getTileFrom(x, y)->getTower();
		
		for (auto attacker : attackers) {
			if (attacker->isInRange(tower->getX(), tower->getY(), tower->getWidth())) {	
				attackersAttacking = true;
				attacker->allowFire(tower);	
			} else { attacker->forbidFire(); }
		}			
	} else {
		for (auto attacker : attackers) {
			attacker->forbidFire();
		}
		attackersAttacking = false;
	}
}

void PlayState::findTargetForTower(const std::shared_ptr<Tower> tower) {
	for (auto attackerIt = attackers.rbegin(); attackerIt != attackers.rend(); ++attackerIt) {
		auto attacker = *attackerIt;
		if (tower->isInRange(attacker->getX(), attacker->getY(), attacker->getWidth())) {
			tower->allowFire(attacker);
			return;
		} 
	}
}

void PlayState::freezeAttackers() {
	for (auto attacker : attackers) {
		attacker->freeze();
	}
}

void PlayState::unfreezeAttackers() {
	for (auto attacker : attackers) {
		attacker->unfreeze();
	}
}

void PlayState::checkGameStatus() {
	if (attackers.empty()) {
		gameStateManager->set(std::shared_ptr<State> (new GameOverState(gameStateManager, "LOSER", score)));
	} else if (attackers.back()->getX() <= -attackers.back()->getWidth()) {
		gameStateManager->set(std::shared_ptr<State> (new GameOverState(gameStateManager, "WINNER", score * attackers.size())));
	}
}
