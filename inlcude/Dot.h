#ifndef DOT_H
#define DOT_H

#include <iostream>
#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Texture.h"

extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;
extern bool checkCollision(std::vector<SDL_Rect> &a, std::vector<SDL_Rect> &b);

class Dot {
public:

    static const int D_W = 20;
    static const int D_H = 20;

    static const int D_Vel = 1;

    Dot(int x, int y);

    void handleEvent(SDL_Event &e);

    void mv(std::vector<SDL_Rect> &otherColliders);

    void render();

    std::vector<SDL_Rect> &getColliders();

    Texture dotTex;


private:

    int xPos, yPos;
    int xVel, yVel;

    std::vector<SDL_Rect> colliders;

    void shiftColliders();

};

#endif // DOT_H
