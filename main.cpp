#include <iostream>
#include <string>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>


const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;


bool init();
bool load();
void close();


void drawBoard();

SDL_Texture* loadTex (std::string path);

SDL_Window* win = NULL;
SDL_Renderer* scr = NULL;

SDL_Texture* tex = NULL;


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

/*
SDL_Texture* loadTex(std::string path) {

    SDL_Texture* newTex = NULL;


    SDL_Surface* loaded = IMG_Load( path.c_str() );

    if (loaded == NULL) {

        std::cout <<"Load image Failed! Error: " << SDL_GetError() << std::endl;

    }
    else {

        newTex = SDL_CreateTextureFromSurface(scr, loaded);
        if(newTex == NULL) {

            std::cout <<"Create Texture Failed! Error: " << SDL_GetError() << std::endl;

        }

        SDL_FreeSurface(loaded);
    }

return newTex;
}
*/

bool load() {

    bool success = true;

   //tex = loadTex("./assets/null.png");

   // if(tex == NULL) {

   //     std::cout <<"Load Failed! Error: "  << SDL_GetError() << std::endl;
   //      success = false;
   //  }

return success;
}

void close() {

    SDL_DestroyTexture(tex);
    tex = NULL;

    SDL_DestroyRenderer(scr);
    scr = NULL;

    SDL_DestroyWindow( win );
    win = NULL;

    std::cout << "Closing...\n";

    IMG_Quit();
    SDL_Quit();

}

void drawBoard() {

    SDL_Rect boardRect = {(SCREEN_WIDTH / 2) - 2,  0, 5, 50};

    for(int i = 0; i < SCREEN_HEIGHT; i++) {

        //SDL_SetRenderDrawColor(scr, 0x00, 0xff, 0x00, 0xff);
       // SDL_RenderDrawLine(scr, SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT);

        SDL_SetRenderDrawColor(scr, 0xff, 0xff, 0xff, 0xff);
        if(i == 0) {

            boardRect.y = -25;
        }
        else {

        boardRect.y += 60;
        }

        SDL_RenderFillRect(scr, &boardRect);
    }
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

                SDL_SetRenderDrawColor(scr, 0x00, 0x00, 0x00, 0xff);
                SDL_RenderClear(scr);

                drawBoard();

                SDL_RenderPresent(scr);
            }
        }
    }

    close();

return 0;
}
