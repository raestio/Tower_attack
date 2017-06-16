#ifndef __game_state_manager_h__
#define __game_state_manager_h__

#include <stack>
#include <memory>
#include <SDL2/SDL.h>


class State;

/**
 * Class manages the game states.
 * It is represented by stack.
 */
class GameStateManager {

 public:
 	/** Push the <b>state</b> on the top. */
	void push(const std::shared_ptr<State> & state);
	
	/** Pop the state from top. */
	void pop();
	
	/** Pop the state from top and push the new <b>state</b> on the top. */
	void set(const std::shared_ptr<State> & state);
	
	/** Handle the inputs from the player. */
	void inputHandle();
	
	/** Update \param deltaTime */
	void update(double deltaTime);
	
	/** Render \param gRenderer*/
	void render(SDL_Renderer * gRenderer) const;
	
 private:
	std::stack< std::shared_ptr<State> > states;
};


#endif /* __game_state_manager_h__ */
