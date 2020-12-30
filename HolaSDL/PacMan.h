#pragma once

#include "Vector2D.h"
#include "Texture.h"
#include "GameCharacter.h"
#include <iostream>

class Game;
//enum MapCell { Wall, Food, Vitamins, Empty };
enum falseBool { cant = 0, can };
using Point2D = Vector2D;
const uint EAT_TIME = 10000;

class PacMan : public GameCharacter
{
private:
	Vector2D nextDir;
	Vector2D dir;
	uint timeVitamin;
	short int canEat;
	
	
public:
	//
	PacMan(Point2D, int, int, Game*, Vector2D, Point2D);
	PacMan(ifstream&,Game*);
	~PacMan();
	bool CanEat();
	virtual void saveToFile(ofstream&);	
	virtual void render() const;
	virtual void update();	
	void handleEvent(const SDL_Event&);
	void reStart();
};

