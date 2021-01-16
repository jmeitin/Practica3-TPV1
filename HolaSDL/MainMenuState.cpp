#include "MainMenuState.h"
#include "Game.h"
#include "PlayState.h"

MainMenuState::MainMenuState(Texture* t, Game* a) : GameState(a) { //mas parametros?
	stage.push_back(new MenuButton(t, pos, width, height, app, playNew));
	stage.push_back(new MenuButton(t, Point2D(pos.getX(), pos.getY()+height), width, height, a, playSaved));
	stage.push_back(new MenuButton(t, Point2D(pos.getX(), pos.getY() + height*2), width, height, a, quit));
}


//jugar nueva partida, cargar partida, salir
void MainMenuState::playNew(Game* app) { //metodo de game que queremos que ejecute al pulsarse
	app->getStateMachine()->changeState(new PlayState());
}

void MainMenuState::playSaved(Game* app) { //metodo de game que queremos que ejecute al pulsarse
	string codigo;

	cout << "Introduzca el codigo numerico del nivel: \n";
	cin >> codigo;
	
	app->getStateMachine()->changeState(new PlayState());
	app->loadSavedGame(codigo); // falta llamar a DirGhost(); //le doy a los fantasmas una direccion inicial
}

void MainMenuState::quit(Game* app) { //metodo de game que queremos que ejecute al pulsarse
	//cerrar pestaña sdl-------------------------------------------------------------------
}