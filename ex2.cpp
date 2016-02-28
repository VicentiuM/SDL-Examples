#include "SDL2/SDL.h"
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren) {
	SDL_Texture *texture = nullptr;
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());

	if (loadedImage != nullptr) {
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);

		if (texture == nullptr)
			logSDLError(std::cout, "CreateTextureFromSurface");
	}
	else 
		logSDLError(std::cout, "LoadBMP");

	return texture;
}

void rendererTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
	SDL_Rect dst;

	dst.x = x;
	dst.y = y;

	//Query the texture to get it's width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
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


	SDL_Texture *background = loadTexture("background.bmp", ren);
	SDL_Texture *image = loadTexture("image.bmp", ren);

	if (background == nullptr || image == nullptr){
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}

	for (int k=0; k<6; k++){
		SDL_RenderClear(ren);

		int bw, bh, iw, ih;
		SDL_QueryTexture(background, NULL, NULL, &bw, &bh);
		for (int i=0; i<=bw; i+=bw)
			for (int j=0; j<=bh; j+=bh)
				rendererTexture(background, ren, i, j);

		SDL_QueryTexture(image, NULL, NULL, &iw, &ih);
		int x = SCREEN_WIDTH / 2 - iw / 2;
		int y = SCREEN_HEIGHT / 2 - ih / 2;
		rendererTexture(image, ren, x, y);

		SDL_RenderPresent(ren);
		SDL_Delay(1000);
	}

	SDL_DestroyTexture(image);
	SDL_DestroyTexture(background);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}