#include "AttackersSelector.h"
#include <string>
#include "../game_objects/Attacker.h"
#include "../map/Tile.h"
#include "../TowerAttack.h"
#include "Label.h"

AttackersSelector::AttackersSelector() {
	attackersAreSelected = false;
	attackersToChoiceCount = ATTACKERS_TO_CHOICE;
	int width = 50;
	attackersCounterLabel = std::shared_ptr<Label> (new Label(std::to_string(attackersToChoiceCount), 
															 TowerAttack::SCREEN_WIDTH / 2 - width / 2,
															 TowerAttack::SCREEN_HEIGHT / 2 - TowerAttack::SCREEN_HEIGHT / 3, 
															 width));
}

void AttackersSelector::setAttackersToChoice(const std::vector< std::shared_ptr<Attacker> > & attackers) {
	attackersToChoice = attackers;
	int x = TowerAttack::SCREEN_WIDTH / 2 - (attackersToChoice.size() / 2) * SPACING * Tile::TILE_DIMENSION;
	int y = TowerAttack::SCREEN_HEIGHT / 2 + 30;
	for (auto & attacker : attackersToChoice) {
		attacker->setPosition(x, y);
		attackersNames.push_back(std::shared_ptr<Label>(new Label(attacker->getName(), x - Tile::TILE_DIMENSION / 2, y - 25, 2 * Tile::TILE_DIMENSION )));
		
		x += SPACING * Tile::TILE_DIMENSION;
	}
}

void AttackersSelector::handleEvent(SDL_Event & e) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	for (auto & attacker : attackersToChoice) {
		if (attacker->isTouched(x, y)) {
			selectedAttackers.push_back(std::shared_ptr<Attacker>(attacker->clone()));
			attackersToChoiceCount--; 		 		
		}
	}
}

void AttackersSelector::update() {
	attackersCounterLabel->setText(std::to_string(attackersToChoiceCount));
	if (attackersToChoiceCount <= 0) { attackersAreSelected = true; }
}

void AttackersSelector::draw(SDL_Renderer * gRenderer) const {
	attackersCounterLabel->draw(gRenderer);
	for (auto & attacker : attackersToChoice) { 
		attacker->draw(gRenderer);
	}
	
	for (auto & label : attackersNames) {
		label->draw(gRenderer);
	}
}

bool AttackersSelector::areAttackersSelected() const { return attackersAreSelected; }

std::vector< std::shared_ptr<Attacker> > AttackersSelector::getSelectedAttackers() const { return selectedAttackers; }
