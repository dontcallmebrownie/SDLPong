#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <string>>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

extern SDL_Renderer* scr;
extern TTF_Font* font;

class Texture {

public:
    Texture();

    ~Texture();

    bool loadFile(std::string path);

    bool loadText(std::string text, SDL_Color textColor);

    void free();

    void setColor(Uint8 r, Uint8 g, Uint8 b);

    void setBlendMode(SDL_BlendMode blending);

    void setAlpha(Uint8 alpha);

    void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip = SDL_FLIP_NONE);

    int getW();
    int getH();

private:
    SDL_Texture* tex;

    int w;
    int h;
};


#endif // TEXTURE_H
