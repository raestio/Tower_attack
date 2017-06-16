#ifndef __game_over_state_h__
#define __game_over_state_h__

#include <SDL2/SDL.h>
#include "State.h"
#include <string>
#include <memory>
#include "../tools/Label.h"

class GameStateManager;

/** Game over state.
 * Displays the score of the player and the game result. By clicking on the screen the game starts again.
 */
class GameOverState : public State {

 public:
 	/**
 	 * Initialize member attributes.
 	 * \param gsm Pointer to GameStateManager.
 	 * \param endGameText Text to be displayed.
 	 * \param score Score of the player.
 	 */
	GameOverState(GameStateManager * gsm, const std::string & endGameText, int score);
	virtual void inputHandle() override;
	virtual void update(double deltaTime) override;
	virtual void render(SDL_Renderer * gRenderer) const override;

 private:
	std::shared_ptr<Label> scoreLabel, endGameLabel;
};

#endif /* __game_over_state_h__ */
