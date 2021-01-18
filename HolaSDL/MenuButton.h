#pragma once
#include "GameObject.h"
#include "EventHandler.h"
#include "Vector2D.h"
#include "Game.h"


using CallBackOnClick = void(Game* app); // puntero a un metodo al que le paso como parametro un puntero a game
const int width = 500;
const int height = 200;

class MenuButton : public GameObject , public EventHandler
{
enum Estado {Nada, Hover, Clicked};

//FACILITA EL INDEXAR EL ARRAY--------------------------------------------------------------------------------------


protected:
	Texture* texture;
	CallBackOnClick* cbOnClick; //puntero a funcion
	Estado estado;

public:
	MenuButton(TextureName, Point2D, Game*, CallBackOnClick*);
	~MenuButton();
	virtual void update();
	virtual void render() const;
	virtual bool handleEvent(SDL_Event&);
};

