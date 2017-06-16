#include "GameStateManager.h"
#include "State.h"

void GameStateManager::push(const std::shared_ptr<State> & state) {	states.push(state); }

void GameStateManager::pop() { states.pop(); }

void GameStateManager::set(const std::shared_ptr<State> & state) {
	states.pop();
	states.push(state);
}

void GameStateManager::inputHandle() { states.top()->inputHandle(); }

void GameStateManager::update(double deltaTime) { states.top()->update(deltaTime); }

void GameStateManager::render(SDL_Renderer * gRenderer) const {	states.top()->render(gRenderer); }

