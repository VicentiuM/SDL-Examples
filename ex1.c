#include "SDL2/SDL.h"
#include <iostream>

int main (int argc, char* args[] ) {

	int i;
if (SDL_Init(SDL_INIT_VIDEO) != 0){
		cout << "SDL_Init Error: " << SDL_GetError() << endl;
		return 1;
	}
	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);


	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


//	std::string imagePath =
	SDL_Surface *bmp = SDL_LoadBMP("LAND2.BMP");


	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);



	for (i=0; i<6; i++){
		//Golim renderur
		SDL_RenderClear(ren);
		//Desenam textura
		SDL_RenderCopy(ren, tex, NULL, NULL);
		//Updatam ecranul
		SDL_RenderPresent(ren);
		//Ia o pauza
		SDL_Delay(1000);
	}

	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}