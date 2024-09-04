#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <string>>

#include <SDL.h>
#include <SDL_image.h>

extern SDL_Renderer* scr;

class Texture {

public:
    Texture();

    ~Texture();

    bool loadFile(std::string path);

    void free();

    void render(int x, int y, SDL_Rect* clip = NULL);

    int getW();
    int getH();

private:
    SDL_Texture* tex;

    int w;
    int h;
};


#endif // TEXTURE_H
