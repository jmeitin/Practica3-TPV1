#pragma once
#include <stack>
#include <string>
//#include "GameObject.h"
#include "GameState.h"

using namespace std;

class GameStateMachine
{
private:
	stack<GameState*> states;
	
public:	
	GameStateMachine(); // no hace nada
	~GameStateMachine();
	void pushState(GameState*);
	void popState();
	void changeState(GameState*);
	GameState* currentState();	
};

