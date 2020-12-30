#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "GameObject.h"
#include <list>
#include <istream>
#include <fstream>
#include <iostream>
using Point2D = Vector2D;

class GameCharacter : public GameObject
{
protected:
	Point2D posIni;
	Vector2D vel; //dir;
	Texture* texture;
	Point2D textureFrame;
	list<GameObject*>::iterator it; 
	
public:	
							//GameObject				 //GameCharacter
	GameCharacter(     Point2D,int,int, Game*      ,Vector2D, Point2D);
	
	GameCharacter(ifstream&,Game*);
	virtual void update() = 0; //virtual ==> enlace dinamico ==> para hacer recorridos polimorficos
	virtual void render() const = 0;	
	virtual void saveToFile(ofstream&);
    void SetItList(list<GameObject*>::iterator);
};

