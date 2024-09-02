#include <iostream>
#include <SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

    std::cout << "hellorld\n";

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else {
        std::cout << "SDL init success!\n";
    }

return 0;
}
