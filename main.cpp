#include <iostream>
#include <string>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


bool init();
bool load();
void close();

SDL_Texture* loadTex (std::string path);

SDL_Window* win = NULL;
SDL_Renderer* scr = NULL;

SDL_Texture* tex = NULL;

//SDL_Surface* img = NULL;
//SDL_Surface* cur = NULL;



bool init() {

    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {

        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        std::cout << "SDL init success!\n";

        win = SDL_CreateWindow ("Hello World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (win == NULL) {
                printf("Window init FAILED Error: %s\n", SDL_GetError());
                success = false;
        }
        else {

            std::cout << "Window init success!\n";

            scr = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
            if(scr == NULL) {

                printf("Create Renderer Failed! Error: %s\n", SDL_GetError());
                success = false;
            }
            else {

                SDL_SetRenderDrawColor(scr, 0x00, 0xFF, 0x00, 0x00);

                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags)) {

                    printf("SDL_Image init Failed! Error: %s\n", IMG_GetError());
                    success = false;
                    }
                }
            }
        }

return success;
}

SDL_Texture* loadTex(std::string path) {

    SDL_Texture* newTex = NULL;


    SDL_Surface* loaded = IMG_Load( path.c_str() );

    if (loaded == NULL) {

        printf("load image Failed! Error: %s\n", SDL_GetError());

    }
    else {

        newTex = SDL_CreateTextureFromSurface(scr, loaded);
        if(newTex == NULL) {

            printf("Create Texture Failed! Error: %s\n", SDL_GetError());

        }

        SDL_FreeSurface(loaded);
    }

return newTex;
}

bool load() {

    bool success = true;

    tex = loadTex("./assets/tex.png");

    if(tex == NULL) {

        printf( "Load Failed! Error: %s\n", SDL_GetError() );
        success = false;
    }

return success;
}


void close() {

    SDL_DestroyTexture(tex);
    tex = NULL;

    SDL_DestroyRenderer(scr);
    scr = NULL;

    SDL_DestroyWindow( win );
    win = NULL;

    printf("Closing...\n");

    IMG_Quit();
    SDL_Quit();

}

int main( int argc, char* argv[] ) {

    if(!init()) {

        printf("Failed to init SDL! \n");
    }
    else {
        if(!load()) {

            printf("Failed to Load img!\n");
        }
        else {

            bool quit = false;

            SDL_Event e;

            while(!quit) {

                while(SDL_PollEvent(&e) != 0) {

                    if(e.type == SDL_QUIT) {

                        quit = true;
                    }
                }

                SDL_RenderClear(scr);

                SDL_RenderCopy(scr, tex, NULL, NULL);

                SDL_RenderPresent(scr);
            }
        }
    }

    close();

return 0;
}
