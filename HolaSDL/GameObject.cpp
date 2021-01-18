#include "GameObject.h"
#include "Game.h"

GameObject::GameObject(Point2D p, int w, int h, Game* g) {
	pos = p;
	width = w;
	height = h;
	app = g;
}
 GameObject::GameObject(ifstream& file, Game * g) {
	 file >> pos >> width >> height;
	 app = g;	
}

GameObject::~GameObject() {

}

//deevuelvo mi SDL_Rect
SDL_Rect GameObject::getDestRect() const{
	return SDL_Rect{ pos.getX(), pos.getY(), width, height };
}
