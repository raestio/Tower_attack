#ifndef __state_h__
#define __state_h__

#include <SDL2/SDL.h>

class GameStateManager;

/** Abstract class represents state of the game. */
class State {

 public:
 	/** Set <b>gameStateManager</b> */
	State(GameStateManager * gameStateManager);
	
	/** Virtual destructor. */
	virtual ~State();
	
	/** Handle the inputs from the player. */
	virtual void inputHandle() = 0;
	
	/**
	 * Update the game state.
	 * \param deltaTime
	 */
	virtual void update(double deltaTime) = 0;
	
	/**
	 * Render the game state.
	 * \param gRenderer
	 */
	virtual void render(SDL_Renderer * gRenderer) const = 0;

 protected:	
	GameStateManager * gameStateManager;
};

#endif /* __state_h__ */
