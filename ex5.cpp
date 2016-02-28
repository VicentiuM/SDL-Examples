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

//Daca clip == nullptr deseneaza intreaga textura
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip = nullptr) {
	SDL_RenderCopy(ren, tex, clip, &dst);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip = nullptr) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;

	if (clip != nullptr) {
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else {
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	}

	renderTexture(tex, ren, dst, clip);
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

	SDL_Texture *image = loadTexture("circle.png", ren);
	if (image == nullptr){
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}

	int iw = 100, ih = 100;
	//SDL_QueryTexture(image, NULL, NULL, &iw, &ih);
	int x = SCREEN_WIDTH / 2 - iw / 2;
	int y = SCREEN_HEIGHT / 2 - ih / 2;

	SDL_Rect clips[4];
	for (int i=0; i<4; i++) {
		clips[i].x = i/2 * iw;
		clips[i].y = i%2 * ih;
		clips[i].w = iw;
		clips[i].h = ih;
	}

	int useClip = 0;

	bool quit = false;
	SDL_Event e;

	while (!quit) {

		while(SDL_PollEvent(&e)){

			if (e.type == SDL_QUIT) {
				quit = true;
			}

			if (e.type == SDL_KEYDOWN) {
				//quit = true;

				switch(e.key.keysym.sym) {
					case SDLK_w:
						y -= 2;
						break;

					case SDLK_a:
						x -= 2;
						break;

					case SDLK_s:
						y += 2;
						break;

					case SDLK_d:
						x += 2;
						break;

					case SDLK_ESCAPE:
						quit = true;
						break;

					case SDLK_1:
						useClip = 0;
						break;

					case SDLK_2:
						useClip = 1;
						break;

					case SDLK_3:
						useClip = 2;
						break;

					case SDLK_4:
						useClip = 3;
						break;
				}
			}

			if (e.type == SDL_MOUSEBUTTONDOWN) {
				quit = true;
			}
		}

		SDL_RenderClear(ren);
		renderTexture(image, ren, x, y, &clips[useClip]);
		SDL_RenderPresent(ren);

	}


	//SDL_Texture *background = loadTexture("background.png", ren);

	SDL_DestroyTexture(image);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}