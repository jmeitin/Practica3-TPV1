#include "MenuButton.h"

MenuButton::MenuButton(Texture* t, Point2D pos, int w, int h, Game* app , CallBackOnClick* cb) : GameObject(pos, w, h, app) { // EventHandler?
	texture = t;
	cbOnClick = cb;
}

MenuButton::~MenuButton() {
	//delete t;
}

void MenuButton::update() {
	//no hace nada
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
