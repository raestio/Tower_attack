#include "MenuState.h"
#include "GameStateManager.h"
#include "../tools/GameManager.h"
#include "../TowerAttack.h"
#include "ChoiceStartState.h"
#include "PlayState.h"
#include "../game_objects/Tower.h"
#include "../game_objects/Attacker.h"
#include "../map/Map.h"
#include "../tools/Timer.h"
MenuState::MenuState(GameStateManager * gsm) : State(gsm) {
	int width = 250;
	for (int i = 1; i <= MAPS_COUNT; ++i) {
		mapLabels.push_back(std::shared_ptr<Label> (new Label(std::string("Map " + std::to_string(i)), i * TowerAttack::SCREEN_WIDTH / 4 - width/2, 30, width)));
	}
	loadLabel = std::shared_ptr<Label> (new Label("Load Game", TowerAttack::SCREEN_WIDTH / 2 - width/2, 200, width));
}

void MenuState::inputHandle() {
	SDL_Event e;
	while (SDL_PollEvent( &e ) != 0) {
		switch (e.type) {
			case SDL_QUIT : throw TowerAttack::QUIT_GAME;
				break;
			case SDL_MOUSEBUTTONDOWN : clickEventHandler(e);
				break;
		}
	}	
}

void MenuState::update(double deltaTime) {}

void MenuState::render(SDL_Renderer * gRenderer) const {
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderClear( gRenderer );
	for (auto label : mapLabels) {
		label->draw(gRenderer);
	}
	loadLabel->draw(gRenderer);
	SDL_RenderPresent( gRenderer );
}

void MenuState::clickEventHandler(const SDL_Event & e) const {
	int x, y;
	SDL_GetMouseState(&x, &y);	
	int i = 1;
	for (auto label : mapLabels) {
		if (label->isTouched(x, y)) {
			gameStateManager->set(std::shared_ptr<State> (new ChoiceStartState(gameStateManager, 
			std::string("assets/maps/" + std::to_string(i) + ".map"))));
			return;
		}
		++i;	
	}
	
	if (loadLabel->isTouched(x, y)) {
		std::shared_ptr<Map> map;
		std::vector< std::shared_ptr<Tower> > towers;
		std::vector< std::shared_ptr<Attacker> > attackers;
		bool attackersAttacking, attackersFrozen;
		int score = 0;
		Timer freezeTimer;
		try {
			GameManager::loadGame(&map, towers, attackers, freezeTimer, attackersAttacking, attackersFrozen, score); 
		} catch (const std::string & str) { 
			return;
		}	
			
		gameStateManager->set(std::shared_ptr<State> (new PlayState(gameStateManager, map, towers, attackers,attackersAttacking, attackersFrozen, freezeTimer, score))); 		
	}
}
