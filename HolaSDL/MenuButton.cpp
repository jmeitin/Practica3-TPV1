#include "MenuButton.h"

MenuButton::MenuButton(Texture* t, Point2D pos, int w, int h, Game* a) : GameObject(pos, w, h, a) { // EventHandler?
	texture = t;
}

MenuButton::~MenuButton() {
	//delete t;
}

void MenuButton::update() {

}

void MenuButton::render() const {

}

bool MenuButton::handleEvent(SDL_Event& event) {
	
}

void MenuButton::OnClick() {

}