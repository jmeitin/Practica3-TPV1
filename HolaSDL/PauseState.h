#pragma once

#include "GameState.h"
#include "MenuButton.h"

class Game;

class PauseState : public  GameState
{
private:	
	Point2D pos; //HAY QUE DARLE UN VALOR -------------------------------------------------------------------
	int width;
	int height;


public:
	PauseState(Texture*, Game*);
	static void resume(Game*);
	static void save(Game*);
	static void backToMenu(Game*);
};
