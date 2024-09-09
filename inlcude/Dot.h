#ifndef DOT_H
#define DOT_H

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Texture.h"

extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;
extern bool checkCollision(SDL_Rect a, SDL_Rect b);

class Dot {
public:

    static const int D_W = 20;
    static const int D_H = 20;

    static const int D_Vel = 10;

    Dot();

    void handleEvent(SDL_Event &e);

    void mv(SDL_Rect &wall);

    void render();

    Texture dotTex;


private:

    int xPos, yPos;
    int xVel, yVel;

    SDL_Rect collider;

};

#endif // DOT_H
