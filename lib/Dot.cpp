#include "Dot.h"

Dot::Dot() {

    xPos = 100;
    yPos = 100;

    xVel = 0;
    yVel = 0;

    collider.w = D_W;
    collider.h = D_H;
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

 void Dot::mv( SDL_Rect &wall) {

    xPos += xVel;
    collider.x = xPos;

    if((xPos < 0) || (xPos + D_W > SCREEN_WIDTH) || checkCollision(collider, wall)) {

        xPos -= xVel;
        collider.x = xPos;
    }

    yPos += yVel;
    collider.y = yPos;
    if((yPos < 0) || ( yPos + D_H > SCREEN_HEIGHT) || checkCollision(collider, wall)) {

      yPos -= yVel;
      collider.y = yPos;
    }
 }

 void Dot::render() {

    dotTex.render(xPos, yPos);
 }
