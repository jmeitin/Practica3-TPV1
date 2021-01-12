#include "PauseState.h"
PauseState::PauseState(Texture* t, Game* app) : GameState(app) { //mas parametros?
	stage.push_back(new MenuButton(t, pos, width, height, app));									   //enverdadesapp
	stage.push_back(new MenuButton(t, Point2D(pos.getX(), pos.getY() + height), width, height, app, resume(app))); //resume es el nombre del metodo
	stage.push_back(new MenuButton(t, Point2D(pos.getX(), pos.getY() + height * 2), width, height, app));
}

static void resume(Game* app){
	game->getStateMachine()->posState();
}