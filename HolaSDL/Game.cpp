#include "Game.h"


using namespace std;

Game::Game() {	
	//inicializacion sdl
	SDL_Init(SDL_INIT_EVERYTHING); //INICIALIZA SDL
	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN); //CREAR VENTANA

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //CREAR Renderer

	if (window == nullptr || renderer == nullptr)
		throw SDLError(SDL_GetError(),"No se ha podido crear window o renderer en Game()");// string("Error cargando window/renderer en SDL");

	for (int i = 0; i < NUM_TEXTURES; ++i) //CREACION TEXTURAS
	{
		textures[i] = new Texture(renderer, imagenesGuardadas + TEXTURES_ATRIBS[i].filename,
			TEXTURES_ATRIBS[i].numRows, TEXTURES_ATRIBS[i].numCols);
		if (textures[i] == nullptr) throw FileNotFound(TEXTURES_ATRIBS[i].filename,"No se ha podido encontrar/cargar la textura");
	}
	//MenuInicial(); //ELEGIR PARTIDA NUEVA/GUARDADA

	gameStateMachine = new GameStateMachine(); //pila de estados vacia
	gameStateMachine->pushState(new MainMenuState(this));
}

void Game::MenuInicial() {
	//char c;	
	//cout << "Introduzca j si quiere JUGAR y c si quiere CARGAR una partida GUARDADA: \n";
	//cin >> c;

	//if (c == 'j') {
	//	loadLevelFile(); //LEE UN ARCHIVO PARA INCIALIZAR LOS ATRIBUTOS
	//	DirGhost(); //le doy a los fantasmas una direccion inicial
	//}

	//else if (c == 'c') {
	/*	string codigo;

		cout << "Introduzca el codigo numerico del nivel: \n";
		cin >> codigo;

		loadSavedGame(codigo);
		DirGhost(); //le doy a los fantasmas una direccion inicial
	//}

	else cout << "Opción no valida";*/
}

//elegir nivel guardado
void Game::MenuGuardar() {
	char c;
	cout << "Introduzca g si quiere guardar la partida: ";
	cin >> c;

	if (c == 'g') {
		string codigo;
		cout << "Introduzca el codigo numerico del nivel: \n";
		cin >> codigo;
		//saveGame(codigo);
	}
	else cout << "Que tenga un buen día.";
}

Game::~Game() {	
	for (Texture* t : textures) delete t;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}



//candidato a emigrar a playState------------------------------------------------------------------------------------------
void Game::run() { //BUCLE PRINCIPAL DEL JUEGO
	int frameTime = 0, startTime = 0, FRAME_RATE = 10;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);//negro

	startTime = SDL_GetTicks();//nos devuelve el tiempo actual en milisegundos 
	
	while (!exitt) {		//get-------------------------------------------------------------------
		getCurrentState()->handleEvents();				
		frameTime = SDL_GetTicks() - startTime;
						
		if (frameTime >= FRAME_RATE || level == GameOver){ //Solo se actualiza cada tanto tiempo
			getCurrentState()->update();
			startTime = SDL_GetTicks();
		}		
		render();		
	}	
}



GameState* Game::getCurrentState() {
     return (gameStateMachine ->currentState());
}


void Game::render() {
	SDL_RenderClear(renderer); //MUESTRA EN EL RENDER EL COLOR ESPECIFICADO POR EL DRAWCOLOR		
	getCurrentState()->render();	
	SDL_RenderPresent(renderer); //MUESTRA EL RENDERIZADO	
}



//DEVUELVE UN PUNTERO A UNA TEXTURA
Texture* Game::getTexture(TextureName text) {
	return textures[text];
}

GameStateMachine* Game::getStateMachine() {
	return gameStateMachine;
}
