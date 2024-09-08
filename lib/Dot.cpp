#include "Dot.h"

Dot::Dot() {

    xPos = 100;
    yPos = 100;

    xVel = 0;
    yVel = 0;
 }

 void Dot::handleEvent(SDL_Event &e) {

    if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {

        switch(e.key.keysym.sym) {

        case SDLK_UP: yVel -= D_Vel; break;
        case SDLK_DOWN: yVel += D_Vel; break;
        case SDLK_LEFT: xVel -= D_Vel; break;
        case SDLK_RIGHT: xVel += D_Vel; break;
        }
    }
    else if(e.type == SDL_KEYUP && e.key.repeat == 0) {

        switch(e.key.keysym.sym) {

        case SDLK_UP: yVel += D_Vel; break;
        case SDLK_DOWN: yVel -= D_Vel; break;
        case SDLK_LEFT: xVel += D_Vel; break;
        case SDLK_RIGHT: xVel -= D_Vel; break;
        }
    }
 }
 void Dot::mv() {

    xPos += xVel;
    if((xPos < 0) || (xPos + D_W > SCREEN_WIDTH)) {

        xPos -= xVel;
    }

    yPos += yVel;
    if((yPos < 0) || ( yPos + D_H > SCREEN_HEIGHT)) {

      yPos -= yVel;
    }
 }

 void Dot::render() {

    dotTex.render(xPos, yPos);
 }
