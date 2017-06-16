#ifndef __play_state_h__
#define __play_state_h__

#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <vector>
#include "../tools/PathFinder.h"
#include "State.h"
#include "../tools/Timer.h"

class Tile;
class GameObject;
class Attacker;
class Tower;
class GameStateManager;
class Map;

/** Play state class. */
class PlayState : public State {

 public:
 	/**
 	 * Initialize member attributes.
 	 * It creates the beginning of the game playing and here is executing path finding algorithm.
 	 * \param gsm Pointer to GameStateManager.
 	 * \param map Map of the game.
 	 * \param deployedTowers Towers that was deployed in TowersDeployment class.
 	 * \param selectedAttackers Attackers that was selected in AttackersSelector class.
 	 * \param startTile Tile where the attackers enter the map.
 	 */
	PlayState(GameStateManager * gsm, const std::shared_ptr<Map> map, 
			  const std::vector< std::shared_ptr<Tower> > & deployedTowers,	const std::vector< std::shared_ptr<Attacker> > & selectedAttackers,
			  const std::shared_ptr<Tile> startTile);
			  
	/**
 	 * This constructor is used for loading the saved play status of the unfinished game.
 	 * It sets up the member parameters and the game will continue.
 	 * \param gsm \param map \param towers \param attackers \param attackersAttacking \param attackersFrozen \param freezeTimer \param score Parameters which were loaded in GameManager class.
 	 */
	PlayState(GameStateManager * gsm, const std::shared_ptr<Map> map, 
			  const std::vector< std::shared_ptr<Tower> > & towers, const std::vector< std::shared_ptr<Attacker> > & attackers,
			  bool attackersAttacking, bool attackersFrozen,
			  const Timer & freezeTimer, int score);
	virtual void inputHandle() override;
	virtual void update(double deltaTime) override;
	virtual void render(SDL_Renderer * gRenderer) const override;

 private:
 	/**
 	 * Handle attackers if the player clicked on the screen.
 	 * If the player clicked on some Tower and some of the attackers is in range then the attacker will be shooting at clicked Tower. 
 	 * \param e SDL_MOUSEBUTTONDOWN event.
 	 */
 	void handleAttackers(SDL_Event & e);
 	
 	/**
 	 * Find the target for the tower to which the tower will be shooting at.
 	 * \param tower For this tower will be targets searched.
 	 */
 	void findTargetForTower(const std::shared_ptr<Tower> tower);
 	
 	/**
 	 * Freeze all attackers in the vector <b>attackers</b>.
 	 */
 	void freezeAttackers();
 	
 	/**
 	 * Unfreeze all attackers in the vector <b>attackers</b>.
 	 */
 	void unfreezeAttackers();
 	
 	/**
 	 * Checking if all attackers have died or have reached the FinishTile. If so the GameOverState will be pushed.
 	 */
 	void checkGameStatus();
	bool attackersAttacking, attackersFrozen;
	std::shared_ptr<Map> map;
	std::vector< std::shared_ptr<Tower> > towers;
	std::vector< std::shared_ptr<Attacker> > attackers;
	PathFinder pathFinder;
	Timer freezeTimer;
	int score;
};

#endif /* __play_state_h__ */
