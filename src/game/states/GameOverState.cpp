#include "GameOverState.h"
#include "../TowerAttack.h"
#include "MenuState.h"

GameOverState::GameOverState(GameStateManager * gsm, const std::string & endGameText, int score) : State(gsm) {
	int labelWidth = 300;
	scoreLabel = std::shared_ptr<Label> (new Label(std::string("Score: " + std::to_string(score)), TowerAttack::SCREEN_WIDTH / 2 - labelWidth / 2, 200, labelWidth));
	endGameLabel = std::shared_ptr<Label> (new Label(endGameText, TowerAttack::SCREEN_WIDTH / 2 - labelWidth / 2, 50, labelWidth));
}

void GameOverState::inputHandle() {
	SDL_Event e;
	while( SDL_PollEvent( &e ) != 0 ) {
		switch (e.type) {
			case SDL_QUIT : throw TowerAttack::QUIT_GAME;
				break;
			case SDL_MOUSEBUTTONDOWN : gameStateManager->set(std::shared_ptr<State> (new MenuState(gameStateManager)));
				return;
		}
	}
}

void GameOverState::update(double deltaTime) {}

void GameOverState::render(SDL_Renderer * gRenderer) const {	
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderClear( gRenderer );

	scoreLabel->draw(gRenderer);
	endGameLabel->draw(gRenderer);	
	
	SDL_RenderPresent(gRenderer);
}
