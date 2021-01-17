#include "MenuButton.h"
#include "Game.h"

MenuButton::MenuButton(TextureName name, Point2D pos, Game* app , CallBackOnClick* cb) : GameObject(pos, width, height, app) { // EventHandler?
	texture = app->getTexture(name);
	cbOnClick = cb;
}

MenuButton::~MenuButton() {
	//no hace na
}

void MenuButton::update() {
	//no hace nada								Text
}

//se renderizan-----------------------------------------------------------------------------------------------------
void MenuButton::render() const {

}

//reaccionan a eventos
bool MenuButton::handleEvent(SDL_Event& ev) {
	if (ev.type == SDL_MOUSEBUTTONUP && ev.button.button == SDL_BUTTON_LEFT) {
		SDL_Point p;//formar punto p y rectangulo r
		SDL_Rect rect = getDestRect();
		if (SDL_PointInRect(&p, &rect) == SDL_TRUE) {
			cbOnClick(game); //app-------------------------------------------------------------------------------------
			return true; //se ha pulsado el boton
		}

		return false; //no se ha pulsado
	}
}
