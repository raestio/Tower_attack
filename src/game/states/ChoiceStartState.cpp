#include "ChoiceStartState.h"
#include "GameStateManager.h"
#include "../game_objects/Tower.h"
#include "../TowerAttack.h"
#include "ChoiceAttackersState.h"
#include "../map/Map.h"
#include "../tools/TowersDeployment.h"
#include <vector>

ChoiceStartState::ChoiceStartState(GameStateManager * gsm, const std::string & mapFilePath) : State(gsm) {
	map = std::shared_ptr<Map>(new Map(mapFilePath));
	gameObjectsLoader.loadGameObjects();
	TowersDeployment::deployTowers(gameObjectsLoader.getTowers(), deployedTowers, map);
	int width = 550;
	textLabel = std::shared_ptr<Label> (new Label("Choose the entrance for attackers", TowerAttack::SCREEN_WIDTH / 2 - width / 2, 5, width));
}

void ChoiceStartState::inputHandle() {
	SDL_Event e;
	while (SDL_PollEvent( &e ) != 0) {
		switch (e.type) {
			case SDL_QUIT : throw TowerAttack::QUIT_GAME;
				break;
			case SDL_MOUSEBUTTONDOWN :
				int x, y;
				SDL_GetMouseState(&x, &y); 
				if (map->isStartTileAt(x, y)) {
			 		gameStateManager->set(std::shared_ptr<State> (new ChoiceAttackersState(gameStateManager, map, deployedTowers, gameObjectsLoader.getAttackers(), map->getTileFrom(x, y))));
			 		return;
			 	}
			 	break;
		}
	}
}

void ChoiceStartState::update(double deltaTime) {}

void ChoiceStartState::render(SDL_Renderer * gRenderer) const {	
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( gRenderer );	
	map->draw(gRenderer);

	for (auto tower : deployedTowers) {
		tower->draw(gRenderer);
	}

	textLabel->draw(gRenderer);
	SDL_RenderPresent(gRenderer);
}
