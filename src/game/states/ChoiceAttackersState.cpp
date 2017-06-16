#include "ChoiceAttackersState.h"
#include "GameStateManager.h"
#include "../game_objects/Tower.h"
#include "../game_objects/Attacker.h"
#include "../TowerAttack.h"
#include "PlayState.h"
#include "../map/Map.h"
#include <SDL2/SDL2_gfxPrimitives.h>

ChoiceAttackersState::ChoiceAttackersState(GameStateManager * gsm, const std::shared_ptr<Map> map, 
										   const std::vector< std::shared_ptr<Tower> > & deployedTowers, const std::vector< std::shared_ptr<Attacker> > & loadedAttackers, 
										   const std::shared_ptr<Tile> startTile) : 
										   State(gsm),  map(map), deployedTowers(deployedTowers), startTile(startTile) {

	attackersSelector.setAttackersToChoice(loadedAttackers);
	int width = 500;
	textLabel = std::shared_ptr<Label> (new Label("Choose attackers", TowerAttack::SCREEN_WIDTH / 2 - width / 2, 0, width));
}

void ChoiceAttackersState::inputHandle() {
	SDL_Event e;
	while ( SDL_PollEvent( &e ) != 0 ) {
		switch (e.type) {
			case SDL_QUIT : throw TowerAttack::QUIT_GAME;
			break;
			case SDL_MOUSEBUTTONDOWN : attackersSelector.handleEvent(e);
			return;
		}
	}
}

void ChoiceAttackersState::update(double deltaTime) {
	attackersSelector.update();
	if (attackersSelector.areAttackersSelected()) {
		gameStateManager->set(std::shared_ptr<State> (new PlayState(gameStateManager, map, deployedTowers, attackersSelector.getSelectedAttackers(), startTile)));
	}
}

void ChoiceAttackersState::render(SDL_Renderer * gRenderer) const {	
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( gRenderer );
	map->draw(gRenderer);
	for (auto tower : deployedTowers) {
		tower->draw(gRenderer);
	}
	boxRGBA(gRenderer, 0, 0, TowerAttack::SCREEN_WIDTH, TowerAttack::SCREEN_HEIGHT, 0, 0 ,0, 200);

	attackersSelector.draw(gRenderer);
	textLabel->draw(gRenderer);
	SDL_RenderPresent(gRenderer);
}
