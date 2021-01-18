#include "GameCharacter.h"
#include "Game.h"
#include "PlayState.h"

using namespace std;

GameCharacter::GameCharacter(Point2D posI, int w, int h, Game* g, Vector2D v, Point2D pText, PlayState* play) : GameObject(posI, w, h, g) {
	posIni = posI;
	vel = v;	
	texture = app->getTexture(CharactersText);
	textureFrame = pText;
	game = play;
}

GameCharacter::GameCharacter(ifstream& file, Game* g, PlayState* play) : GameObject(file,g){
	file >> posIni >> vel >> textureFrame;
	game = play;
	texture= app->getTexture(CharactersText);
}

void GameCharacter::saveToFile(ofstream& file) {
	file << pos << " " << width << " " << height <<  " " << posIni << " " << vel<<" "<<textureFrame; //<<" "//<< texture <<" "<< textureFrame;
}

void GameCharacter::SetItList(list<GameObject*>::iterator yo) {
	it = yo;
}