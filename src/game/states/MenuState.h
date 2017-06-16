#ifndef __menu_state_h__
#define __menu_state_h__

#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include "State.h"
#include "../tools/Label.h"

class GameStateManager;

/** Class displays the menu of the game. */
class MenuState : public State {

 public:
 	/**
 	 * Initialize member attributes.
 	 * \param gsm Pointer to GameStateManager.
 	 */
	MenuState(GameStateManager * gsm);
	
	virtual void inputHandle() override;
	virtual void update(double deltaTime) override;
	virtual void render(SDL_Renderer * gRenderer) const override;
	const int MAPS_COUNT = 3; /**< Number of maps. */

 private:
 	/**
 	 * Handle click event.
 	 * User is choosing either maps that he wants to play or to load the last saved unfinished game.  
 	 */
 	void clickEventHandler(const SDL_Event & e) const;
 	std::shared_ptr<Label> loadLabel;
 	std::vector< std::shared_ptr<Label> > mapLabels;
};

#endif /* __menu_state_h__ */
