// Lang headers
#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>
#include <sstream>

// Library headers
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

// Custom headers
#include "Texture.h"
#include "Button.h"

// Display Var
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Func Protos
bool init();
bool load();
void close();

// Display related Globals
SDL_Window* win = NULL;
SDL_Renderer* scr = NULL;

// Sprite Var
Texture promptTex;
Texture timeTex;

// Audio Var

// Text Var
TTF_Font* font = NULL;


bool init() {

    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {

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

                if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {

                    std::cout << "Failed to init SDL_Mixer! Error: " << Mix_GetError() << std::endl;
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
    if(font == NULL) {

        std::cout << "Failed to load! Error: " << TTF_GetError() << std::endl;
        success = false;
    }
    else {

        SDL_Color textColor = {0, 0, 0, 255};

        if(!promptTex.loadText("Press enter to reset start time.", textColor)) {

            std::cout << "Unable to Render Texture from font!\n";
            success = false;
        }
    }

return success;
}

void close() {


    promptTex.free();
    timeTex.free();
    TTF_CloseFont(font);

    SDL_DestroyRenderer(scr);
    scr = NULL;

    SDL_DestroyWindow( win );
    win = NULL;

    std::cout << "Closing...\n";

    Mix_Quit();
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

            SDL_Color textColor = {0, 0, 0, 255};

            Uint32 startTime = 0;

            std::stringstream timeText;

            while(!quit) {

                while(SDL_PollEvent(&e) != 0) {

                    if(e.type == SDL_QUIT) {

                        quit = true;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {

                        startTime = SDL_GetTicks();

                    }
                }

                timeText.str("");
                timeText << "Milliseconds since start time: " << SDL_GetTicks() - startTime;

                if(!timeTex.loadText(timeText.str().c_str(), textColor)) {

                    std::cout << "Unable to render time texture!\n";
                }

                SDL_SetRenderDrawColor(scr, 0xff, 0x00, 0xff, 0xff);
                SDL_RenderClear(scr);

                // Actual code goes here
                promptTex.render((SCREEN_WIDTH - promptTex.getW()) / 2, 0);

                                                                    //Div by 2 pushes
                                                                    // timer off screen
                timeTex.render((SCREEN_WIDTH - timeTex.getW()) - 50 /* / 2 */, (SCREEN_HEIGHT - timeTex.getH()) / 2);


                SDL_RenderPresent(scr);

                }
            }
        }

    close();

return 0;
}
