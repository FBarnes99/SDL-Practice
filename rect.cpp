#include "rect.h"
#include <SDL_image.h>
#include <iostream>


Rect::Rect(const Window &window ,int w, int h, int x, int y, int r, int g, int b, int a) :
Window(window),	_w(w), _h(h), _x(x), _y(y), _r(r), _g(g), _b(b), _a(a)
{


}

Rect::Rect(const Window &window, int w, int h, int x, int y,const string &image_path) :
	Window(window), _w(w), _h(h), _x(x), _y(y)
{
	SDL_Surface *surface = IMG_Load(image_path.c_str());

	if (!surface) {
		cerr << "Failed to create surface";
	}
	_texture = SDL_CreateTextureFromSurface(_renderer, surface);

	if (!_texture) {
		cerr << "Failed to create texture";
	}
	SDL_FreeSurface(surface);
}

Rect::~Rect() {
	SDL_DestroyTexture(_texture);


}

void Rect::draw() const {
	SDL_Rect rect = { _x, _y, _w,_h };
	
	if (_texture) {
		SDL_RenderCopy(_renderer, _texture, nullptr, &rect);
	}
	else
	{ 
	SDL_SetRenderDrawColor(_renderer, _r, _g, _b, _a);
	SDL_RenderFillRect(_renderer, &rect);
	}
}

void Rect::pollEvents(SDL_Event &event) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
			_x -= 10;
			break;
		case SDLK_RIGHT:
			_x += 10;
			break;
		case SDLK_UP:
			_y -= 10;
			break;
		case SDLK_DOWN:
			_y += 10;
			break;
		
		
			
			
			break;

		}

	}

}