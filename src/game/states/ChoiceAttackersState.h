#ifndef __choice_attackers_state_h__
#define __choice_attackers_state_h__

#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <vector>

#include "State.h"
#include "../game_objects/GameObject.h"
#include "../tools/AttackersSelector.h"
#include "../tools/Label.h"

class GameStateManager;
class Map;
class Tower;
class Attacker;

/** State in which the player chooses the attackers. */
class ChoiceAttackersState : public State {

 public:
 	/**
 	 * Initialize member attributes.
 	 * \param gsm Pointer to GameStateManager.
 	 * \param map Map of the game.
 	 * \param deployedTowers Towers.
 	 * \param loadedAttackers Attackers.
 	 */
	ChoiceAttackersState(GameStateManager * gsm, const std::shared_ptr<Map> map, 
						 const std::vector< std::shared_ptr<Tower> > & deployedTowers, const std::vector< std::shared_ptr<Attacker> > & loadedAttackers,
						 const std::shared_ptr<Tile> startTile);
	virtual void inputHandle() override;
	virtual void update(double deltaTime) override;
	virtual void render(SDL_Renderer * gRenderer) const override;

 private:
	std::shared_ptr<Map> map;
	std::vector< std::shared_ptr<Tower> > deployedTowers;
	std::shared_ptr<Tile> startTile;
	AttackersSelector attackersSelector;
	std::shared_ptr<Label> textLabel;
};

#endif /* __choice_attackers_state_h__ */
