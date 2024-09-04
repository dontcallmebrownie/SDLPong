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

Texture modTex;
Texture bgTex;


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

    if(!modTex.loadFile("./assets/fadeout.png")) {

        std::cout << "Failed to load fadeout!\n";
        success = false;
    }
    else {

        modTex.setBlendMode(SDL_BLENDMODE_BLEND);
    }

    if(!bgTex.loadFile("./assets/fadein.png")) {

        std::cout << "Failed to load BG!\n";
        success = false;
    }

return success;
}

void close() {

    modTex.free();
    bgTex.free();

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

            Uint8 a = 255;


            while(!quit) {

                while(SDL_PollEvent(&e) != 0) {

                    if(e.type == SDL_QUIT) {

                        quit = true;
                    }
                    else if(e.type == SDL_KEYDOWN) {

                        if(e.key.keysym.sym == SDLK_w) {

                            if(a + 32 > 255) {

                                a = 255;
                            }
                            else {
                                a += 32;
                            }
                        }
                        else if(e.key.keysym.sym == SDLK_s) {

                            if(a - 32 < 0) {

                                a = 0;
                            }
                            else {

                                a -= 32;
                            }
                        }
                    }
                }

                    SDL_SetRenderDrawColor(scr, 0xff, 0x00, 0xff, 0xff);
                    SDL_RenderClear(scr);

                    bgTex.render(0, 0);
                    modTex.setAlpha(a);

                    modTex.render(0, 0);

                    SDL_RenderPresent(scr);



            }
        }
    }



    close();

return 0;
}
