// Language Headers
#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>

// Library Headers
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// Custom Headers
#include "Texture.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


bool init();
bool load();
void close();


SDL_Window* win = NULL;
SDL_Renderer* scr = NULL;

TTF_Font* font = NULL;
Texture textTex;


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

            scr = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

                if(TTF_Init() == -1) {

                    std::cout << "Failed to init SDL_ttf! Error: " << TTF_GetError() << std::endl;
                    success = false;
                }
            }
        }
    }

return success;
}

bool load() {

    bool success = true;

    font = TTF_OpenFont("./assets/lazy.ttf", 28);
    if(font ==NULL) {

        std::cout << "Failed to load Font! Error: " << TTF_GetError() << std::endl;
        success = false;
    }
    else {

        SDL_Color textColor = {0, 0, 0};
        if(! textTex.loadText("The quick brown fox jumps over the lazy dog", textColor)) {

            std::cout << "Failed to render text texture!\n";
            success = false;
        }
    }

return success;
}

void close() {

    textTex.free();

    TTF_CloseFont(font);
    font = NULL;

    SDL_DestroyRenderer(scr);
    scr = NULL;

    SDL_DestroyWindow( win );
    win = NULL;

    std::cout << "Closing...\n";

    TTF_Quit();
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

            double degrees = 0;

            SDL_RendererFlip flipT = SDL_FLIP_NONE;

            while(!quit) {

                while(SDL_PollEvent(&e) != 0) {

                    if(e.type == SDL_QUIT) {

                        quit = true;
                    }
                }

                SDL_SetRenderDrawColor(scr, 0xff, 0x00, 0xff, 0xff);
                SDL_RenderClear(scr);

                // Actual code goes here                                                                // Div by 2 puts the text
                                                                                                        // off screen at this res
                textTex.render((SCREEN_WIDTH - textTex.getW()) / 2, (SCREEN_HEIGHT - textTex.getH() * 2 /* / 2 */));


                SDL_RenderPresent(scr);

                }
            }
        }




    close();

return 0;
}
