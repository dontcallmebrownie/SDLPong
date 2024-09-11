#include "Dot.h"

Dot::Dot(int x, int y) {

    xPos = x;
    yPos = y;

    colliders.resize(11);

    xVel = 0;
    yVel = 0;

    colliders[0].w = 6;
    colliders[0].h = 1;

    colliders[1].w = 10;
    colliders[1].h = 1;

    colliders[2].w = 14;
    colliders[2].h = 1;

    colliders[3].w = 16;
    colliders[3].h = 2;

    colliders[4].w = 18;
    colliders[4].h = 2;

    colliders[5].w = 20;
    colliders[5].h = 6;

    colliders[6].w = 18;
    colliders[6].h = 2;

    colliders[7].w = 16;
    colliders[7].h = 2;

    colliders[8].w = 14;
    colliders[8].h = 1;

    colliders[9].w = 10;
    colliders[9].h = 1;

    colliders[10].w = 6;
    colliders[10].h = 1;

    shiftColliders();
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

 void Dot::mv(std::vector<SDL_Rect> &otherColliders) {

    xPos += xVel;
    shiftColliders();

    if((xPos < 0) || (xPos + D_W > SCREEN_WIDTH) || checkCollision(colliders, otherColliders)) {

        xPos -= xVel;
        shiftColliders();
    }

    yPos += yVel;
    shiftColliders();

    if((yPos < 0) || ( yPos + D_H > SCREEN_HEIGHT) || checkCollision(colliders, otherColliders)) {

      yPos -= yVel;
      shiftColliders();
    }
 }

 void Dot::render() {

    dotTex.render(xPos, yPos);
 }


 void Dot::shiftColliders() {

    int r = 0;

    for(int set = 0; set < colliders.size(); ++ set) {

        colliders[set].x = xPos + (D_W - colliders[set].w / 2);

        colliders[set].y = yPos + r;

        r += colliders[set].h;
    }
 }

 std::vector<SDL_Rect> &Dot::getColliders() {

return colliders;
 }

