#include <iostream>
#include <string>

#include <SDL.h>
#include <stdio.h>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum keyPressSurf {

KEY_PRESS_DEF,
KEY_PRESS_UP,
KEY_PRESS_DOWN,
KEY_PRESS_LEFT,
KEY_PRESS_RIGHT,
KEY_PRESS_TOTAL

};

bool init();
bool load();
void close();

SDL_Surface* loadSurface (std::string path);

SDL_Window* win = NULL;
SDL_Surface* scr = NULL;

SDL_Surface* keyPres[ KEY_PRESS_TOTAL ];
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

    keyPres[KEY_PRESS_DEF] = loadSurface( "./assets/press.bmp" );

    if( keyPres[ KEY_PRESS_DEF ] == NULL ) {

        printf( "Load Failed! Error: %s\n", SDL_GetError() );
        success = false;
    }

    keyPres[KEY_PRESS_UP] = loadSurface( "./assets/up.bmp" );

    if( keyPres[ KEY_PRESS_UP ] == NULL ) {

        printf( "Load Failed! Error: %s\n", SDL_GetError() );
        success = false;
    }

    keyPres[KEY_PRESS_DOWN] = loadSurface( "./assets/down.bmp" );

    if( keyPres[ KEY_PRESS_DOWN ] == NULL ) {

        printf( "Load Failed! Error: %s\n", SDL_GetError() );
        success = false;
    }

    keyPres[KEY_PRESS_LEFT] = loadSurface( "./assets/left.bmp" );

    if( keyPres[ KEY_PRESS_LEFT ] == NULL ) {

        printf( "Load Failed! Error: %s\n", SDL_GetError() );
        success = false;
    }

    keyPres[KEY_PRESS_RIGHT] = loadSurface( "./assets/right.bmp" );

    if( keyPres[ KEY_PRESS_RIGHT ] == NULL ) {

        printf( "Load Failed! Error: %s\n", SDL_GetError() );
        success = false;
    }

return success;
}

SDL_Surface* loadSurface( std::string path ) {

    SDL_Surface* loaded = SDL_LoadBMP( path.c_str() );

    if (loaded == NULL) {

        printf("load bmp Failed! Error: %s\n", SDL_GetError());

    }

return loaded;
}

void close() {

    for(int i = 0; i < KEY_PRESS_TOTAL; ++i) {

        SDL_FreeSurface(keyPres[i]);
        keyPres[i] = NULL;
    }

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

            cur = keyPres[KEY_PRESS_DEF];

            while(!Q) {

                while(SDL_PollEvent(&e) !=0) {

                    if(e.type == SDL_QUIT) {

                        Q = true;
                    }

                    switch(e.key.keysym.sym) {
                        case SDLK_UP:
                            cur = keyPres[KEY_PRESS_UP];
                            break;
                        case SDLK_DOWN:
                            cur = keyPres[KEY_PRESS_DOWN];
                            break;
                        case SDLK_LEFT:
                            cur = keyPres[KEY_PRESS_LEFT];
                            break;
                        case SDLK_RIGHT:
                            cur = keyPres[KEY_PRESS_RIGHT];
                            break;
                        default:
                            cur = keyPres[KEY_PRESS_DEF];
                            break;
                    }

                    SDL_BlitSurface( cur, NULL, scr, NULL);

                    SDL_UpdateWindowSurface(win);
                }
            }
        }
    }

    close();

return 0;
}
