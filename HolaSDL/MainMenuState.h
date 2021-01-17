#pragma once

#include "GameState.h"
#include "MenuButton.h"

class Game;

class MainMenuState : public  GameState
{
private:
	Point2D pos; //HAY QUE DARLE UN VALOR -------------------------------------------------------------------
	

	TextureName playText = PlayText;
	TextureName restartText = RestartText;
	TextureName exitText = ExitText;

public:
	MainMenuState(Game*);
	static void playNew(Game*);
	static void playSaved(Game*);
	static void quit(Game*);
};

