#include "SmartGhost.h"
#include "Game.h"
#include "PlayState.h"

using namespace std;

SmartGhost::SmartGhost(Point2D posI, int w, int h, Game* g, Vector2D v, Point2D pText, PlayState* play) : Ghost(posI, w, h, g, v, pText,play) {
	state = Child;
	tVivo = SDL_GetTicks();
}

SmartGhost::SmartGhost(ifstream& file, Game* g, PlayState* play) : Ghost(file, g, play) {
	int estado;
	file >> estado;
	state = (State)estado;

	file >> tVivo;
}

SmartGhost::~SmartGhost(){

}

void SmartGhost::render() const {
	SDL_Rect myRect = getDestRect();
	if (state == Child) {
		myRect.w = myRect.w / 2;
		myRect.h = myRect.h / 2;
	}	
	texture->renderFrame(myRect, textureFrame.getX(), textureFrame.getY());
}

void SmartGhost::update() {
	handleState();
	if(state != Dead)
	FollowNotFollow();
}

void SmartGhost::FollowNotFollow() {
	bool moverse = false;
	if (SDL_GetTicks() > mov1 + TIEMPO1) {
		Point2D difPos;
		int distance;
		vector<Vector2D> followChoices;
		vector<Vector2D> notFollow;
		
		game->FollowPlayer(pos, difPos, distance);

		if (distance < 150) { //estoy a cierto rango
			//<= => incializo FollowChoices y NotFollow
			if (difPos.getX() > 0) {
				followChoices.push_back(posdir[este]);
				notFollow.push_back(posdir[oeste]);
			}
			else if (difPos.getX() < 0) {
				followChoices.push_back(posdir[oeste]);
				notFollow.push_back(posdir[este]);
			}
			if (difPos.getY() > 0) {
				followChoices.push_back(posdir[sur]);
				notFollow.push_back(posdir[norte]);
			}
			else if (difPos.getY() < 0) {
				followChoices.push_back(posdir[norte]);
				notFollow.push_back(posdir[sur]);
			}
			

			if (!game->PacmanCanEat())
				Move(followChoices, notFollow); //SI PACMAN NO PUEDE COMER ==> le sigo

			else Move(notFollow, followChoices);

		}
		else {
			Ghost::update();
			moverse = true;
		}//si estoy fuera de rango ==> me muevo random

	} //fin del if control de tiempo
	if (!moverse) {
		Point2D newPos;
		if (game->TryMove(getDestRect(), dir.direc, newPos)) pos = newPos;
	}
}


void SmartGhost::saveToFile(ofstream& file) {
	file << 3 << '\n'; //IDENTIFICADOR
	Ghost::saveToFile(file);
	file << state << ' ' << tVivo << '\n';
}



void SmartGhost::Move(const vector<Vector2D>& go, const vector<Vector2D>& notGo) {
	vector<Vector2D> choices;
	vector<int> indices;

	int iOpuesto = dir.indice;//valor inicial

	for (int x = 0; x < go.size(); x++) {
		if (game->TryMove(getDestRect(), go[x], Point2D(0, 0))) {
			choices.push_back(go[x]); //POSIBLE DIR EN LA QUE MOVERME	
			indices.push_back(x);
		}
	}

	//calculo de la proxima dir
	if (choices.size() > 0) {
		int random = rand() % choices.size();
		dir.indice = indices[random];
		dir.direc = choices[random];
		mov1 = SDL_GetTicks();
	}
}

//puedo reproducirme o no
bool SmartGhost::canBreed() {
	return (state == Adult || state == Quarantine);
}

void SmartGhost::handleState() {
	//si soy child y pasa x tiempo me vuelvo adulto
	if (state == Child && SDL_GetTicks() > TiempoChild + tVivo) {
		state = Adult;
		tVivo = SDL_GetTicks();
	}

	else if (state == Adult) {
		//si me reproduzco me meto en cuarentena
		if (game->GhostsCollide(this)) {
			state = Quarantine;
			tQuar = SDL_GetTicks();
		}
		//si no, pasado x tiempo me muero
		if (SDL_GetTicks() > tVivo + tDeath) {
			state = Dead;
			tVivo = SDL_GetTicks();
		}
	}
	else if (state == Quarantine && SDL_GetTicks() > tQuar + tCuarentena)	
		state == Adult;
	//muerto desaparezco en un tiempo
	else if (state == Dead && SDL_GetTicks() > tVivo + tDeath / 3) 
		game->EraseGhost(it);
}




