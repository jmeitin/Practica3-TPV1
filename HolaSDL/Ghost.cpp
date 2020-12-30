#include "Ghost.h"
#include "Game.h"
#include <vector>
#include <iostream>
		
Ghost::Ghost(Point2D posI, int w, int h, Game* g, Vector2D v, Point2D pText) : GameCharacter(posI, w, h, g, v, pText) {

	posdir[norte] = Vector2D(0, -1);
	posdir[este] = Vector2D(1, 0);
	posdir[oeste] = Vector2D(-1, 0);
	posdir[sur] = Vector2D(0, 1);
	dir.direc = Vector2D(0, 0);
	
}
Ghost::Ghost(ifstream& file, Game* g) : GameCharacter(file, g) {
	posdir[norte] = Vector2D(0, -1);
	posdir[este] = Vector2D(1, 0);
	posdir[oeste] = Vector2D(-1, 0);
	posdir[sur] = Vector2D(0, 1);
	dir.direc = Vector2D(0, 0);
}
Ghost::~Ghost() {

}

void Ghost::render()const{ //CONSTRUIRSE Y DIBUJARSE	
	SDL_Rect myRect = getDestRect();
	/*myRect.y = (pos.getY() * myRect.h) + (myRect.h / 2);
	myRect.x = (pos.getX() * myRect.w) + (myRect.w / 2);*/
									//0					//depende del valor que se le pase cuando se cree el mapa
	texture->renderFrame(myRect, textureFrame.getX(), textureFrame.getY());
	
} // 0 norte, 1 este, 2 sur, 3 oeste

// voy al norte y me sale sur 0, 2
//voy al sur y me sale norte 2, 0



			//   0
			//3     1
			//   2

void Ghost::getDirIndice() {
	//cout << textureFrame.getY();
	vector<Vector2D> choices;
	for (int x = 0; x < posdir.size(); x++) { 
		Point2D posibili;//vamos chulos		
		if (game->TryMove(getDestRect(),posdir[x], posibili)) {
			choices.push_back(posdir[x]); //POSIBLE DIR EN LA QUE MOVERME			
		}		
	}
	//if(choices.size() == 0);
	int random = rand() % choices.size();
	dir.indice = random;		
}

void Ghost::getDir() {
	if (SDL_GetTicks() > mov + TIEMPO) {
		vector<Vector2D> choices;
		vector<int> indices;
		int iOpuesto = dir.indice;//valor inicial

		for (int x = 0; x < posdir.size(); x++) { //vamos chulos
			int iAct = dir.indice;
			int dif = abs(x - iAct); //VALOR ABSOLUTO 2-3 = |1|


			//SI LA DIF NO ES 2, NO ES EL OPUESTO ==> COMPRUEBO QUE NO ES PARED
			if (dif != 2 && game->TryMove(getDestRect(), posdir[x], Point2D(0,0)) ) {
				choices.push_back(posdir[x]); //POSIBLE DIR EN LA QUE MOVERME	
				indices.push_back(x);
			}
			else if (dif == 2) iOpuesto = x; //GUARDO LA DIR OPUESTA
		}

		if (choices.size() < 1) { //NO ENCONTRO NINGUNA 
			dir.indice = iOpuesto;
			dir.direc = posdir[iOpuesto]; //Y SI HAY PARED DETRAS?? ATRAPADO
		}
		else {
			int random = rand() % choices.size();
			dir.indice = indices[random];
			dir.direc = choices[random];

		}
		mov = SDL_GetTicks();
	}
	Point2D newPos;
	if(game->TryMove(getDestRect(),dir.direc, newPos)) pos = newPos;
}

void Ghost::update(){ //SE MUEVE, CAMBIAR DIR DE FORMA ALEATORIA
//UTILIZARA Game* PARA VER SI ESE MOVIMIENTO SE PUEDE REALIZAR	
	
	getDir();	
}

void Ghost::saveToFile(ofstream& file) {
	file << 1 << '\n'; //IDENTIFICADOR

	GameCharacter::saveToFile(file);
	
	file << '\n';
}

Point2D Ghost::getPos() { 
   return pos; 
}


void Ghost::die(){ //MUERE ==> VUELVE A LA POS INI
	pos = posIni;
	/// DIR Y DIREC :/
}

