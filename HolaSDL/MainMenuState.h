#pragma once

#include "GameState.h"
#include "MenuButton.h"
#include "PlayState.h"

class Game;

class MainMenuState : public  GameState
{
	

private:
	Point2D pos; //HAY QUE DARLE UN VALOR -------------------------------------------------------------------


public:
	MainMenuState(Game*);
	static void playNew(Game*);
	static void playSaved(Game*);
	static void quit(Game*);
};

