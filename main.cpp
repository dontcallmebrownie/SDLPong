#include <iostream>
#include <SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;



int main( int argc, char* argv[] ) {

    SDL_Window* win = NULL;
    SDL_Surface* scr = NULL;


    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else {
        std::cout << "SDL init success!\n";

        win = SDL_CreateWindow ( "Hello World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if ( win == NULL ) {
                printf("Window init FAILED Error: %s\n", SDL_GetError() );
        }
        else {
            std::cout << "Window init success!\n";

            scr = SDL_GetWindowSurface( win );

            SDL_FillRect( scr, NULL, SDL_MapRGB( scr->format, 0xFF, 0xFF, 0xFF ) );

            SDL_UpdateWindowSurface( win );




            SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
        }
    }

     SDL_DestroyWindow( win );
     SDL_Quit();



return 0;
}
