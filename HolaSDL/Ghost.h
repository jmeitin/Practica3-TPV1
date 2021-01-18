#pragma once

#include "Vector2D.h"
#include "Texture.h"
#include <array>
#include "GameCharacter.h"
#include <vector>
#include <iostream>

class PlayState;
class Game;

using Point2D = Vector2D;

class Ghost : public GameCharacter
{
	struct Direction {
		short int indice;
		Vector2D direc;	//no es un puntero
	};
	
	
protected:		
	int mov;
	const int TIEMPO = 300;
	enum direcciones { norte = 0, este , sur , oeste };
	uint32_t startTime, frameTime;
	//int posS;
	array<Vector2D, 4> posdir;
	Direction dir;
	
	void getDir();
public:
	Ghost(Point2D , int , int , Game* , Vector2D , Point2D , PlayState*);
	Ghost(ifstream&,Game*, PlayState*);
	~Ghost();
	Point2D getPos();
	void getDirIndice();	
	virtual void saveToFile(ofstream&);
	virtual void render() const;
	virtual void update();	
	void die(); 
};

