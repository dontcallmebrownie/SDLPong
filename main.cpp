#include <iostream>
#include <string>

#include <SDL.h>
#include <stdio.h>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


bool init();
bool load();
void close();

SDL_Surface* loadSurface (std::string path);

SDL_Window* win = NULL;
SDL_Surface* scr = NULL;

SDL_Surface* img = NULL;
SDL_Surface* cur = NULL;



bool init() {

    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {

        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );

        success = false;
    }
    else {
        std::cout << "SDL init success!\n";

        win = SDL_CreateWindow ( "Hello World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

        if ( win == NULL ) {
                printf("Window init FAILED Error: %s\n", SDL_GetError() );

                success = false;
        }
        else {

            std::cout << "Window init success!\n";

            scr = SDL_GetWindowSurface( win );
        }
    }

return success;
}

bool load() {

    bool success = true;

    img = loadSurface( "./assets/stretch.bmp" );

    if( img == NULL ) {

        printf( "Load Failed! Error: %s\n", SDL_GetError() );
        success = false;
    }

return success;
}

SDL_Surface* loadSurface( std::string path ) {

    SDL_Surface* optSurf = NULL;


    SDL_Surface* loaded = SDL_LoadBMP( path.c_str() );

    if (loaded == NULL) {

        printf("load bmp Failed! Error: %s\n", SDL_GetError());

    }
    else {
        optSurf = SDL_ConvertSurface(loaded, scr->format, 0);
        if(optSurf == NULL) {

            printf("Optimize img Failed! Error: %s\n", SDL_GetError());

        }

        SDL_FreeSurface(loaded);
    }

return optSurf;
}

void close() {

    SDL_FreeSurface(img);
    img = NULL;


    SDL_DestroyWindow( win );
    win = NULL;

    printf("Closing...\n");

    SDL_Quit();

}

int main( int argc, char* argv[] ) {

    if( !init() ) {

        printf("Failed to init SDL! \n");
    }
    else {
        if( !load() ) {

            printf("Failed to Load img!\n");
        }
        else {

            bool Q = false;

            SDL_Event e;

            while(!Q) {

                while(SDL_PollEvent(&e) !=0) {

                    if(e.type == SDL_QUIT) {

                        Q = true;
                    }

                    SDL_Rect stretch;
                    stretch.x = 0;
                    stretch.y = 0;
                    stretch.w = SCREEN_WIDTH;
                    stretch.h = SCREEN_HEIGHT;


                    SDL_BlitScaled( img, NULL, scr, &stretch);

                    SDL_UpdateWindowSurface(win);

                }
            }
        }
    }

    close();

return 0;
}
