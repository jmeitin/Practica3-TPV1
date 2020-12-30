#include "GameStateMachine.h"

GameStateMachine::GameStateMachine() { //no hace nada

}

GameStateMachine::~GameStateMachine() {
	while (!states.empty()) popState();
}

void GameStateMachine::pushState(GameState* state) {
	states.push(state);
}

void GameStateMachine::popState() {
	if (!states.empty()) { 
		delete states.top();
		states.pop(); 
	}
	else throw "La pila de GameStateMachine esta vacía.";
}

void GameStateMachine::changeState(GameState* state) {
	popState();
	pushState(state);
}

GameState* GameStateMachine::currentState() {
	if (!states.empty()) return states.top();
	else throw "La pila de GameStateMachine esta vacía.";
}
