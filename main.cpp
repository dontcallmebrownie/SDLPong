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

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

   enum ButtonSpr {

    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
    };

bool init();
bool load();
void close();

// Display related Globals
SDL_Window* win = NULL;
SDL_Renderer* scr = NULL;

class Button
{
public:
    Button();

    void setPos(int x, int y);

    void handleEvent(SDL_Event* e);

    void render();



private:
    SDL_Point pos;

    ButtonSpr curSpr;
};

SDL_Rect sprClips[BUTTON_SPRITE_TOTAL];
Texture buttonSprSheet;


Button::Button() {

    pos.x = 0;
    pos.y = 0;

    curSpr = BUTTON_SPRITE_MOUSE_OUT;
}

void Button::setPos(int x, int y) {

    pos.x = x;
    pos.y = y;
}

void Button::handleEvent(SDL_Event* e) {

    if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {

        int x, y;
        SDL_GetMouseState(&x, &y);

        bool inside = true;

        if(x < pos.x) {

            inside = false;
        }
        else if(x > pos.x + BUTTON_WIDTH) {

            inside = false;
        }
        else if(y < pos.y) {

            inside = false;
        }
        else if (y > pos.y + BUTTON_HEIGHT) {

            inside = false;
        }

        if(!inside) {

            curSpr = BUTTON_SPRITE_MOUSE_OUT;
        }
        else {

            switch (e->type) {
            case SDL_MOUSEMOTION:
                curSpr = BUTTON_SPRITE_MOUSE_OVER;
                break;
            case SDL_MOUSEBUTTONDOWN:
                curSpr = BUTTON_SPRITE_MOUSE_DOWN;
                break;
            case SDL_MOUSEBUTTONUP:
                curSpr = BUTTON_SPRITE_MOUSE_UP;
                break;
            }
        }
    }
}

void Button::render() {

    buttonSprSheet.render(pos.x, pos.y, &sprClips[curSpr]);
}

// Sprite Var

Button buttons[TOTAL_BUTTONS];

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

    if(!buttonSprSheet.loadFile("./assets/button.png")) {

        std::cout << "Failed to load Sprite sheet!\n";
        success = false;
    }
    else {

        for(int i = 0; i < BUTTON_SPRITE_TOTAL; ++i) {

            sprClips[i].x = 0;
            sprClips[i].y = i * 200;
            sprClips[i].w = BUTTON_WIDTH;
            sprClips[i].h = BUTTON_HEIGHT;
        }

        buttons[0].setPos( 0, 0 );
		buttons[1].setPos( SCREEN_WIDTH - BUTTON_WIDTH, 0 );
		buttons[2].setPos( 0, SCREEN_HEIGHT - BUTTON_HEIGHT );
		buttons[3].setPos( SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT );
    }

return success;
}

void close() {

    buttonSprSheet.free();

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


            while(!quit) {

                while(SDL_PollEvent(&e) != 0) {

                    if(e.type == SDL_QUIT) {

                        quit = true;
                    }

                    for(int i = 0; i < TOTAL_BUTTONS; ++i) {

                        buttons[i].handleEvent(&e);
                    }
                }


                SDL_SetRenderDrawColor(scr, 0xff, 0x00, 0xff, 0xff);
                SDL_RenderClear(scr);

                // Actual code goes here
                for(int i = 0; i < TOTAL_BUTTONS; ++i) {

                    buttons[i].render();
                }

                SDL_RenderPresent(scr);

                }
            }
        }




    close();

return 0;
}
