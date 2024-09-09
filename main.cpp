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
#include "Timer.h"
#include "Dot.h"
//#include "Button.h"
// TODO:
//      The code originally used with the Button class
//      doesn't work, figure this out!
//      Should be pretty easy tbh, just require new render code.

// Display Var
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const int SCREEN_TICKSPF = 1000 / SCREEN_FPS;

// Func Protos
bool init();
bool load();
void close();
bool checkCollision(SDL_Rect a, SDL_Rect b);

// Display related Globals
SDL_Window* win = NULL;
SDL_Renderer* scr = NULL;

// Sprite Var
Dot dot;

//Texture
Texture FPSTex;


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

    if(!dot.dotTex.loadFile("./assets/dot.bmp")) {

        std::cout << "Couldn't load dot.bmp!\n";
    }


return success;
}

void close() {

    FPSTex.free();
    dot.dotTex.free();

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

bool checkCollision(SDL_Rect a, SDL_Rect b) {

    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int botA, botB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    botA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    botB = b.y + b.h;

    if(botA <= topB){

        return false;
    }

    if(topA >= botB){

        return false;
    }

    if(rightA <= leftB){

        return false;
    }

    if(leftA >= rightB){

        return false;
    }

return true;
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

            Timer fpsTimer;
            Timer capTimer;

            std::stringstream timeText;

            int countedFrames = 0;
            fpsTimer.start();

            SDL_Rect wall;
            wall.x = 300;
            wall.y = 40;
            wall.w = 40;
            wall.h = 400;

            while(!quit) {

                capTimer.start();

                while(SDL_PollEvent(&e) != 0) {

                    if(e.type == SDL_QUIT) {

                        quit = true;
                    }

                    dot.handleEvent(e);
                }

                // Actual code goes here
                float avgFps = countedFrames / (fpsTimer.getTicks() / 1000.f);
                if(avgFps > 2000000) {

                    avgFps = 0;
                }

                timeText.str("");
                timeText << "FPS: " << avgFps;

                if(!FPSTex.loadText(timeText.str().c_str(), textColor)) {

                    std::cout << "Unable to render time texture!\n";
                }

                    dot.mv(wall);

                    SDL_SetRenderDrawColor(scr, 0xff, 0x00, 0xff, 0xff);
                    SDL_RenderClear(scr);

                    SDL_SetRenderDrawColor(scr, 0x00, 0x00, 0x00, 0xff);
                    SDL_RenderDrawRect(scr, &wall);
                    dot.render();
                    FPSTex.render((FPSTex.getW() - 100), (FPSTex.getH()));

                    SDL_RenderPresent(scr);
                    ++countedFrames;

                    int frameTicks = capTimer.getTicks();
                    if(frameTicks < SCREEN_TICKSPF) {

                        SDL_Delay(SCREEN_TICKSPF - frameTicks);
                    }

                }
            }
        }

    close();

return 0;
}
