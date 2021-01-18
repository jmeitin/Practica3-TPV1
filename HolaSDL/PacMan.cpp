#include "PacMan.h"
#include "Game.h"
#include "PlayState.h"


PacMan::PacMan (Point2D posI, int w, int h, Game* g, Vector2D v, Point2D pText, PlayState* play) : GameCharacter(posI, w, h, g, v, pText,play) {
	canEat = cant;		
	dir = Vector2D(0, 0);
	nextDir = Vector2D(0, 0);	
}

PacMan::PacMan(ifstream& file, Game* g, PlayState* play) : GameCharacter(file,g,play) {
	canEat = cant;
	dir = Vector2D(0, 0);
	nextDir = Vector2D(0, 0);
}

PacMan::~PacMan() {
	
}

void PacMan::render()  const{	
	SDL_Rect myRect = getDestRect();

	texture->renderFrame(myRect, 0, 10 + canEat);
}

void PacMan::handleEvent(const SDL_Event &event) {		
		switch (event.key.keysym.sym) {
			case SDLK_UP:					
				nextDir.setDir(0,-1);
				break;
			case SDLK_LEFT:
				nextDir.setDir(-1, 0);
				break;
			case SDLK_DOWN:
				nextDir.setDir(0, 1);
				break;
			case SDLK_RIGHT:
				nextDir.setDir(1, 0);
				break;
	    }		
}


bool PacMan::CanEat() {
	return (canEat == 1);
}

void PacMan::update() {
	Point2D newPoint = pos;
	Point2D newPoint1 = pos;
	static_cast<PlayState*>(app->getCurrentState())->checkGhost(pos,canEat);
	
	// si puedo cambiar de direccion lo hago	
	if (game->TryMove(getDestRect(), nextDir, newPoint)) { // si me puedo mover en esa nextDir, lo hago
		dir = nextDir;
        pos = newPoint;		
	}

	//si no, trato de moverme en la dir actual
	else if (game->TryMove(getDestRect(), dir, newPoint1)) pos = newPoint1;
   
	//una vez ya tengo la posicion actualizada ==> compruebo lo que hay en esa casilla	
	switch (game->CheckCell(pos)) {
	  case Food:
		  game->MinusFood(game->SDLPointToMapCoords(pos));
		break;

	  case Vitamins:
		canEat = can;
		game->MinusFood(game->SDLPointToMapCoords(pos));
		timeVitamin = SDL_GetTicks();
		break;
	}
	
	game->checkGhost(pos, canEat);
	
	if (canEat == can && SDL_GetTicks() > timeVitamin + EAT_TIME) canEat = cant;
}

void PacMan::saveToFile(ofstream& file){ 
	file << 0 << '\n'; //IDENTIFICADOR

	GameCharacter::saveToFile(file);
	
	file << '\n';
}


void PacMan::reStart() {
	pos = posIni;
}

