#include "GameState.h"
#include "Game.h"

GameState::GameState(Game* a) { //faltarian parametros-----------------------------------------------------------------------------------------
	app = a;
	//list<GameObject*> stage;
	//list<EventHandler*> eventhandlers;
}

GameState::~GameState() {
    for(GameObject* o: stage) delete o;
}

void GameState::render() {
    for(GameObject* o: stage) o->update();
}

void GameState::update() {
    for(GameObject* o: stage) o->render();
}

void GameState::handleEvent(SDL_Event& event) {
    for(EventHandler* e: eventhandlers)  if(e->handleEvent(event)) break;
}
