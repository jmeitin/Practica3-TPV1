#pragma once
#include <list>
#include "SDL.h"
#include "GameObject.h"
#include "EventHandler.h"

class Game;

using namespace std;

class GameState
{
protected:
	list<GameObject*> stage;
	list<EventHandler*> eventhandlers;
	Game* app;

	GameState(Game*); //.... recibiria mas cosas

public:
	~GameState();
	virtual void render();
	virtual void update();
	void handleEvent(SDL_Event&);
};

