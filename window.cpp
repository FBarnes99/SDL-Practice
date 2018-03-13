#include "Window.h"
#include <iostream>
#include <SDL.h>
#include  <SDL_image.h>
using namespace std;

Window::Window(const string &title, int width, int height) :
	_width(width) , _title(title),  _height(height)
{

	_closed =  !init();
}

Window::~Window() {
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	IMG_Quit();
	SDL_Quit();

}

bool Window::init() {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cerr << "Failed";
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		cerr << "Failed to initialize image";
	}

	_window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, 0);

	if(_window == nullptr){
		cerr << "Failed to crate window";
		return false;
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	
	if (_renderer == nullptr) {

		cerr << "Failed to crate renderer";
		return false;
	}



	return true;
}

void Window::pollEvents(SDL_Event &event) {
	switch (event.type) {
	case SDL_QUIT:
		_closed = true;
		break;

	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case  SDLK_ESCAPE:
			_closed = true;
			break;

		}


	default:
		break;
	}

}

void Window :: clear()const {
	SDL_RenderPresent(_renderer);
	
	SDL_SetRenderDrawColor(_renderer, 0, 0, 200, 255);
	

	SDL_RenderClear(_renderer);
	
}