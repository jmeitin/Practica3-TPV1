#include "MainMenuState.h"

MainMenuState::MainMenuState(Texture* t, Game* a) : GameState(a) { //mas parametros?
	stage.push_back(new MenuButton(t, pos, width, height, a));
	stage.push_back(new MenuButton(t, Point2D(pos.getX(), pos.getY()+height), width, height, a));
	stage.push_back(new MenuButton(t, Point2D(pos.getX(), pos.getY() + height*2), width, height, a));
}

bool MainMenuState::handleEvent(SDL_Event& e){
	if () { //sis se pulsa
		//ejecuta accion
		return true;
	}
	return false;
}