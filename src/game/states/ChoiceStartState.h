#ifndef __choice_start_state_h__
#define __choice_start_state_h__

#include <SDL2/SDL.h>
#include <iostream>
#include <memory>

#include "State.h"
#include "../tools/GameObjectsLoader.h"
#include "../game_objects/GameObject.h"
#include "../tools/Label.h"
#include <string>

class GameStateManager;
class Map;

/** State in which the player chooses the map's entry for the attackers. */
class ChoiceStartState : public State {

 public:
  	/** Initialize member attributes.
  	 * \param gsm Pointer to GameStateManager.
  	 * \param mapFilePath Path to the map file.
  	 */
	ChoiceStartState(GameStateManager * gsm, const std::string & mapFilePath);
	virtual void inputHandle() override;
	virtual void update(double deltaTime) override;
	virtual void render(SDL_Renderer * gRenderer) const override;

 private:
	std::shared_ptr<Map> map;
	std::vector< std::shared_ptr<Tower> > deployedTowers;
	GameObjectsLoader gameObjectsLoader;
	std::shared_ptr<Label> textLabel;
};

#endif /* __choice_start_state_h__ */
