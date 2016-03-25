#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#include <SDL2/SDL.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event e;

int x=50, y=50, w=50, h=50;
SDL_Rect r;


void mainloop() {
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    SDL_RenderClear( renderer );

    while(SDL_PollEvent(&e)) {

        if( e.type == SDL_QUIT ) {
            //Quit the program
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            exit(0);
        }


        if (e.type == SDL_KEYDOWN) {
            switch(e.key.keysym.sym) {
                case SDLK_w:
                    r.y -= 2;
                    break;
                case SDLK_a:
                    r.x -= 2;
                    break;
                case SDLK_s:
                    r.y += 2;
                    break;
                case SDLK_d:
                    r.x += 2;
                    break;
            }
        }
    }

    
    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
    SDL_RenderFillRect( renderer, &r );
    SDL_RenderPresent(renderer);


}

int main(int argc, char * args[]) {    


    printf("Use wasd to move the square");

    window = SDL_CreateWindow
    (
        "Moving Square using SDL2", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_SHOWN
    );

    renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
    
    r.x = 50;
    r.y = 50;
    r.w = 50;
    r.h = 50;


    #ifdef EMSCRIPTEN
        emscripten_set_main_loop(mainloop, 10, 0);
    #else
        while(1)
            mainloop();
    #endif    

    return 0;
}