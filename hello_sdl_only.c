#include "SDL/SDL.h"

int main (int argc, char* args[] ) {

	//Declaram pointeri pentru cele 2 imagini, una ecranul si una mesajul
	SDL_Surface* hello = NULL;
	SDL_Surface* screen = NULL;

	//Start SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	//Set up screen
	screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);

	//Load image
	hello = SDL_LoadBMP("LAND2.BMP");


	//Apply image to screen
	SDL_BlitSurface(hello, NULL, screen, NULL);

	//Update Screen
	SDL_Flip(screen);

	//Pause tine imaginea timp de 2 secunde pe ecran
	SDL_Delay(2000);

	//Free the loaded image
	SDL_FreeSurface(hello);

	//Quit SDL
	SDL_Quit();

	return 0;
}