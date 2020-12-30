#pragma once
#include "Vector2D.h"
#include "Texture.h"

class Game;
using Point2D = Vector2D;

class GameObject
{
protected:
	Point2D pos;
	int width, height;
	Game* game;

public:
	GameObject(Point2D, int, int, Game*);
	GameObject(ifstream&, Game*);
	virtual ~GameObject();	
	virtual void update() = 0; //practica 3
	
	
	virtual void render() const = 0; //igual a 0 ==> abstracto. le furezas a que haga los de los demas?
	virtual SDL_Rect getDestRect() const;
};

