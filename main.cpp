#include <iostream>
#include <string>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Texture.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


bool init();
bool load();
void close();


SDL_Window* win = NULL;
SDL_Renderer* scr = NULL;

SDL_Rect sprClips[4];
Texture sprSheet;


bool init() {

    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {

       std::cout << "SDL could not initialize! SDL_Error:" << SDL_GetError() << std::endl;
        success = false;
    }
    else {
        std::cout << "SDL init success!\n";

        win = SDL_CreateWindow ("Hello World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (win == NULL) {
                std::cout << "Window init FAILED Error: " << SDL_GetError() << std::endl;
                success = false;
        }
        else {

            std::cout << "Window init success!\n";

            scr = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
            if(scr == NULL) {

                std::cout << "Create Renderer Failed! Error: " << SDL_GetError() << std::endl;
                success = false;
            }
            else {

                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags)) {

                    std::cout << "SDL_Image init Failed! Error: " << IMG_GetError() << std::endl;
                    success = false;
                }
            }
        }
    }

return success;
}

bool load() {

    bool success = true;

    if(!sprSheet.loadFile("./assets/dots.png")) {

        std::cout << "Failed to load spritesheet!\n";
        success = false;
    }
    else {

        sprClips[0].x = 0;
        sprClips[0].y = 0;
        sprClips[0].w = 100;
        sprClips[0].h = 100;

        sprClips[1].x = 100;
        sprClips[1].y = 0;
        sprClips[1].w = 100;
        sprClips[1].h = 100;

        sprClips[2].x = 0;
        sprClips[2].y = 100;
        sprClips[2].w = 100;
        sprClips[2].h = 100;

        sprClips[3].x = 100;
        sprClips[3].y = 100;
        sprClips[3].w = 100;
        sprClips[3].h = 100;
    }

return success;
}

void close() {

    sprSheet.free();

    SDL_DestroyRenderer(scr);
    scr = NULL;

    SDL_DestroyWindow( win );
    win = NULL;

    std::cout << "Closing...\n";

    IMG_Quit();
    SDL_Quit();

}

int main( int argc, char* argv[] ) {

    if(!init()) {

        std::cout << "Failed to init SDL! \n";
    }
    else {
        if(!load()) {

            std::cout << "Failed to Load img!\n";
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

                SDL_SetRenderDrawColor(scr, 0xff, 0x00, 0xff, 0xff);
                SDL_RenderClear(scr);

                sprSheet.render(0, 0, &sprClips[0]);
                sprSheet.render(SCREEN_WIDTH - sprClips[1].w, 0, &sprClips[1]);
                sprSheet.render(0, SCREEN_HEIGHT - sprClips[2].h, &sprClips[2]);
                sprSheet.render(SCREEN_WIDTH - sprClips[3].w, SCREEN_HEIGHT - sprClips[3].h, &sprClips[3]);

                SDL_RenderPresent(scr);
            }
        }
    }

    close();

return 0;
}
