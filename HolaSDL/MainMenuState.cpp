#include "MainMenuState.h"
#include "Game.h" //texturas

MainMenuState::MainMenuState(Game* a) : GameState(a) { //mas parametros?
	stage.push_back(new MenuButton(PlayText, pos, a, playNew));
	eventhandlers.push_back(static_cast<EventHandler*>(stage.front()));
	stage.push_back(new MenuButton (RestartText, Point2D(pos.getX(), pos.getY()+height), a, playSaved));
	stage.push_back(new MenuButton(ExitText, Point2D(pos.getX(), pos.getY() + height*2), a, quit));
}


//jugar nueva partida, cargar partida, salir
void MainMenuState::playNew(Game* app) { //metodo de game que queremos que ejecute al pulsarse
	app->getStateMachine()->changeState(new PlayState(app));
}

void MainMenuState::playSaved(Game* app) { //metodo de game que queremos que ejecute al pulsarse
	string codigo;

	cout << "Introduzca el codigo numerico del nivel: \n";
	cin >> codigo;

	PlayState* game = new PlayState(app);
	app->getStateMachine()->changeState(game);
	game->loadSavedGame(codigo); // falta llamar a DirGhost(); //le doy a los fantasmas una direccion inicial
}

void MainMenuState::quit(Game* app) { //metodo de game que queremos que ejecute al pulsarse
	//cerrar pestaña sdl-------------------------------------------------------------------
	SDL_Quit();
}