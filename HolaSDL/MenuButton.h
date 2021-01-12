#pragma once
#include "GameObject.h"
#include "EventHandler.h"

using CallBackOnClick = void(Game* app); //?

class MenuButton : public GameObject , public EventHandler
{
protected:
	Texture* texture;
	CallBackOnClick* cbOnClick; //puntero a funcion

public:
	MenuButton(Texture*, Point2D, int, int, Game*, CallBackOnClick*);
	~MenuButton();
	virtual void update();
	virtual void render() const;
	virtual bool handleEvent(SDL_Event&);
	void OnClick();
};

