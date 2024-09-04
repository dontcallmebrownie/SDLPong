#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Texture.h"
#include "Button.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool load();
void close();

// Display related Globals
SDL_Window* win = NULL;
SDL_Renderer* scr = NULL;

// Sprite Var
Texture presTex;
Texture upTex;
Texture downTex;
Texture leftTex;
Texture rightTex;

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

    int numLoaded = 0;

    if(!presTex.loadFile("./assets/press.png")) {

        std::cout << "Failed to load! Texture #: 0\n";
        success = false;
    }
    else if(!upTex.loadFile("./assets/up.png")) {

        std::cout << "Failed to load! Texture #: 1\n";
        success = false;
    }
    else if(!downTex.loadFile("./assets/down.png")) {

        std::cout << "Failed to load! Texture #: 2\n";
        success = false;
    }
    else if(!leftTex.loadFile("./assets/left.png")) {

        std::cout << "Failed to load! Texture #: 3\n";
        success = false;
    }
    else if(!rightTex.loadFile("./assets/right.png")) {

        std::cout << "Failed to load! Texture #: 4\n";
        success = false;
    }


return success;
}

void close() {

    presTex.free();
    upTex.free();
    downTex.free();
    leftTex.free();
    rightTex.free();

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

            Texture* curTex = NULL;

            while(!quit) {

                while(SDL_PollEvent(&e) != 0) {

                    if(e.type == SDL_QUIT) {

                        quit = true;
                    }
                }

                const Uint8* curKeyState = SDL_GetKeyboardState(NULL);
                if(curKeyState[SDL_SCANCODE_UP]){

                    curTex = &upTex;
                }
                else if(curKeyState[SDL_SCANCODE_DOWN]){

                    curTex = &downTex;
                }
                else if(curKeyState[SDL_SCANCODE_LEFT]){

                    curTex = &leftTex;
                }
                else if(curKeyState[SDL_SCANCODE_RIGHT]){

                    curTex = &rightTex;
                }
                else {

                    curTex = &presTex;
                }


                SDL_SetRenderDrawColor(scr, 0xff, 0x00, 0xff, 0xff);
                SDL_RenderClear(scr);

                // Actual code goes here
                curTex->render(0, 0);

                SDL_RenderPresent(scr);

                }
            }
        }




    close();

return 0;
}
