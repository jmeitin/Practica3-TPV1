#include "MenuButton.h"
#include "Game.h"

MenuButton::MenuButton(TextureName name, Point2D pos, Game* app , CallBackOnClick* cb) : GameObject(pos, width, height, app) { // EventHandler?
	texture = app->getTexture(name);
	cbOnClick = cb;
	estado = Nada;
}

MenuButton::~MenuButton() {
	//no hace na
}

void MenuButton::update() {
	//no hace nada								Text
}

//se renderizan-----------------------------------------------------------------------------------------------------
void MenuButton::render() const {
	SDL_Rect myRect = getDestRect();	
	texture->renderFrame(myRect, 0, estado);
}

//reaccionan a eventos
bool MenuButton::handleEvent(SDL_Event& ev) {
	SDL_Point p;//formar punto p y rectangulo r
	SDL_Rect rect = getDestRect();
	if (SDL_PointInRect(&p, &rect) == SDL_TRUE) { // si el raton esta encima
		estado = Hover;
		if ((ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT)) {
			estado = Clicked;
			cbOnClick(app); //app-------------------------------------------------------------------------------------
			return true; //se ha pulsado el boton
		}
		else return false;
	}
	//if (ev.type == SDL_MOUSEBUTTONUP && ev.button.button == SDL_BUTTON_LEFT) {
	//	SDL_Point p;//formar punto p y rectangulo r
	//	SDL_Rect rect = getDestRect();
	//	if (SDL_PointInRect(&p, &rect) == SDL_TRUE) {
	//		cbOnClick(app); //app-------------------------------------------------------------------------------------
	//		return true; //se ha pulsado el boton
	//	}

	//	return false; //no se ha pulsado
	//}
}
