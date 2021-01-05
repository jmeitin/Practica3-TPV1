#pragma once

#include "GameState.h"
#include "MenuButton.h"

class PauseState : public  GameState
{
private:
	Point2D pos; //HAY QUE DARLE UN VALOR -------------------------------------------------------------------
	int width;
	int height;


public:
	PauseState(Texture*, Game*);
	bool handleEvent(SDL_Event&);
};
