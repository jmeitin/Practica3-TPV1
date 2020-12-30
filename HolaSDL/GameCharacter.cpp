#include "GameCharacter.h"
#include "Game.h"
using namespace std;

GameCharacter::GameCharacter(Point2D posI, int w, int h, Game* g, Vector2D v, Point2D pText) : GameObject(posI, w, h, g) {
	posIni = posI;
	vel = v;	
	texture = game->getTexture(CharactersText);
	textureFrame = pText;
}

GameCharacter::GameCharacter(ifstream& file, Game* g) : GameObject(file,g){
	file >> posIni >> vel >> textureFrame; 	
	texture= game->getTexture(CharactersText);
}

void GameCharacter::saveToFile(ofstream& file) {
	file << pos << " " << width << " " << height <<  " " << posIni << " " << vel<<" "<<textureFrame; //<<" "//<< texture <<" "<< textureFrame;
}

void GameCharacter::SetItList(list<GameObject*>::iterator yo) {
	it = yo;
}