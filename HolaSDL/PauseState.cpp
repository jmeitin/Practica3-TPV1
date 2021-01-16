#include "PauseState.h"
#include "Game.h"
#include "MainMenuState.h"

PauseState::PauseState(Texture* t, Game* app) : GameState(app) { //mas parametros?
	stage.push_back(new MenuButton(t, pos, width, height, app, resume)); //resume es el nombre del metodo	   //enverdadesapp
	stage.push_back(new MenuButton(t, Point2D(pos.getX(), pos.getY() + height), width, height, app, save)); 
	stage.push_back(new MenuButton(t, Point2D(pos.getX(), pos.getY() + height * 2), width, height, app, backToMenu));
}
	
//resume, save, back to menu
void PauseState::resume(Game* app){ //metodo de game que queremos que ejecute al pulsarse
	app->getStateMachine()->popState();
}

void PauseState::save(Game* app) { //metodo de game que queremos que ejecute al pulsarse
	app->MenuGuardar(); //guardar partida
	//te quedas en el menu por si quiere seguir jugando o volver al menu incial
}

void PauseState::backToMenu(Game* app) { //metodo de game que queremos que ejecute al pulsarse	
	app->getStateMachine()->changeState(new MainMenuState(texture, app)); //-------------------------------------------------------------------
}
