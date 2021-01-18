#pragma once

#include "GameState.h"
#include "MenuButton.h"
#include "MainMenuState.h"

class Game;

class PauseState : public  GameState
{
	//FACILITA EL INDEXAR EL ARRAY------------------------------------------------------------------------
	

private:	
	Point2D pos; //HAY QUE DARLE UN VALOR -------------------------------------------------------------------
	

	//resume, save, back to menu
	

public:
	PauseState(Game*);
	static void resume(Game*);
	static void save(Game*);
	static void backToMenu(Game*);
};
