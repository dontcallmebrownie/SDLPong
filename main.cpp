// Lang headers
#include <iostream>
#include <string>
#include <stdio.h>
#include <cmath>

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

// Audio Var
Mix_Music* music = NULL;

Mix_Chunk* scratch = NULL;
Mix_Chunk* high = NULL;
Mix_Chunk* medium = NULL;
Mix_Chunk* low = NULL;

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

    if(!promptTex.loadFile("./assets/prompt.png")) {

        std::cout << "Failed to load texture!\n";
        success = false;
    }

    music = Mix_LoadMUS("./assets/beat.wav");
    if(music == NULL) {

        std::cout << "Failed to load .wav file! Error: " << Mix_GetError() << std::endl;
        success = false;
    }

    scratch = Mix_LoadWAV("./assets/scratch.wav");
    if( scratch == NULL) {

        std::cout << "Failed to load .wav file! Error: " << Mix_GetError() << std::endl;
        success = false;
    }

    high = Mix_LoadWAV("./assets/high.wav");
    if( high == NULL) {

        std::cout << "Failed to load .wav file! Error: " << Mix_GetError() << std::endl;
        success = false;
    }

    medium = Mix_LoadWAV("./assets/medium.wav");
    if( medium == NULL) {

        std::cout << "Failed to load .wav file! Error: " << Mix_GetError() << std::endl;
        success = false;
    }

    low = Mix_LoadWAV("./assets/low.wav");
    if( low == NULL) {

        std::cout << "Failed to load .wav file! Error: " << Mix_GetError() << std::endl;
        success = false;
    }

return success;
}

void close() {

    promptTex.free();

    Mix_FreeChunk(scratch);
    Mix_FreeChunk(high);
    Mix_FreeChunk(medium);
    Mix_FreeChunk(low);

    scratch = NULL;
    high = NULL;
    medium = NULL;
    low = NULL;

    Mix_FreeMusic(music);
    music = NULL;



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

            while(!quit) {

                while(SDL_PollEvent(&e) != 0) {

                    if(e.type == SDL_QUIT) {

                        quit = true;
                    }
                    else if(e.type == SDL_KEYDOWN) {

                        switch (e.key.keysym.sym) {

                        case SDLK_1:
                            Mix_PlayChannel(-1, high, 0);
                            break;
                        case SDLK_2:
                            Mix_PlayChannel(-1, medium, 0);
                            break;
                        case SDLK_3:
                            Mix_PlayChannel(-1, low, 0);
                            break;
                        case SDLK_4:
                            Mix_PlayChannel(-1, scratch, 0);
                            break;
                        case SDLK_9:
                            if(Mix_PlayingMusic() == 0) {

                                Mix_PlayMusic(music, -1);
                            }
                            else {
                                if(Mix_PausedMusic() == 1) {

                                    Mix_ResumeMusic();
                                }
                                else {

                                    Mix_PauseMusic();
                                }
                            }
                            break;
                        case SDLK_0:
                            Mix_HaltMusic();
                            break;

                        }
                    }
                }

                SDL_SetRenderDrawColor(scr, 0xff, 0x00, 0xff, 0xff);
                SDL_RenderClear(scr);

                // Actual code goes here
                promptTex.render(0,0);

                SDL_RenderPresent(scr);

                }
            }
        }

    close();

return 0;
}
