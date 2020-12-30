#pragma once
#include "GameObject.h"
#include "EventHandler.h"

class MenuButton : public GameObject , public EventHandler
{
protected:
	Texture* texture;

public:
	MenuButton(Texture*, Point2D, int, int, Game*);
	~MenuButton();
	virtual void update();
	virtual void render() const;
	virtual bool handleEvent(SDL_Event&);
	void OnClick();
};

