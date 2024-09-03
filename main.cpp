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

                SDL_SetRenderDrawColor(scr, 0x00, 0x00, 0x00, 0xff);

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
/*
    tex = loadTex("./assets/tex.png");

    if(tex == NULL) {

        printf( "Load Failed! Error: %s\n", SDL_GetError() );
        success = false;
    }
*/
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

                SDL_SetRenderDrawColor(scr, 0xff, 0xff, 0xff, 0xff);
                SDL_RenderClear(scr);

                SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
                SDL_SetRenderDrawColor(scr, 0xff, 0x00, 0x00, 0xff);
                SDL_RenderFillRect(scr, &fillRect);

                SDL_Rect outlineRect = {SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 /3, SCREEN_HEIGHT * 2 /3};
                SDL_SetRenderDrawColor(scr, 0x00, 0xFF, 0x00, 0xff);
                SDL_RenderDrawRect(scr, &outlineRect);

                SDL_SetRenderDrawColor(scr, 0x00, 0x00, 0xff, 0xff);
                SDL_RenderDrawLine(scr, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

                SDL_SetRenderDrawColor(scr, 0xff, 0xff, 0x00, 0xff);
                for(int i = 0; i < SCREEN_HEIGHT; i += 4) {

                    SDL_RenderDrawPoint(scr, SCREEN_WIDTH / 2, i);
                }

                SDL_RenderPresent(scr);
            }
        }
    }

    close();

return 0;
}
