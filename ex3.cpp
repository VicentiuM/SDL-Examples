#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_SIZE = 40;

void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren) {
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());

	if (texture == nullptr)
		logSDLError(std::cout, "LoadTexture");

	return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h) {
	SDL_Rect dst;

	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;

	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	renderTexture(tex, ren, x, y, w, h);
}

int main (int argc, char* args[] ) {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (win == nullptr){
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (ren == nullptr){
		logSDLError(std::cout, "CreateRenderer");
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}


	SDL_Texture *background = loadTexture("background.png", ren);
	SDL_Texture *image = loadTexture("image.png", ren);

	if (background == nullptr || image == nullptr){
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}

	for (int k=0; k<6; k++){
		SDL_RenderClear(ren);

		int bw, bh, iw, ih;
		//SDL_QueryTexture(background, NULL, NULL, &bw, &bh);
/*
		for (int i=0; i<TILE_SIZE; i++)
			for (int j=0; j<=TILE_SIZE; j++)
				renderTexture(background, ren, i * (SCREEN_WIDTH / TILE_SIZE), j * (SCREEN_HEIGHT / TILE_SIZE));
*/

		for (int i = 0; i < SCREEN_WIDTH / TILE_SIZE; i++) 
			for (int j = 0; j < SCREEN_HEIGHT / TILE_SIZE; j++)
				renderTexture(background, ren, i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE);
	


		SDL_QueryTexture(image, NULL, NULL, &iw, &ih);
		int x = SCREEN_WIDTH / 2 - iw / 2;
		int y = SCREEN_HEIGHT / 2 - ih / 2;
		renderTexture(image, ren, x, y);

		SDL_RenderPresent(ren);
		SDL_Delay(1000);
	}

	SDL_DestroyTexture(image);
	SDL_DestroyTexture(background);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}