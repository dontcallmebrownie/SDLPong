#include "Texture.h"

Texture::Texture()
{
    tex = NULL;
    w = 0;
    h = 0;
}

Texture::~Texture()
{
    free();
}

bool Texture::loadFile(std::string path){

    free();

    SDL_Texture* newTex = NULL;

    SDL_Surface* loaded = IMG_Load(path.c_str());
    if(loaded == NULL) {

        std::cout << "Load file Failed! Error: " << IMG_GetError() << std::endl;
    }
    else {

        SDL_SetColorKey(loaded, SDL_TRUE, SDL_MapRGB(loaded->format, 0, 0xff, 0xff));

        newTex = SDL_CreateTextureFromSurface(scr, loaded);
        if(newTex == NULL) {

            std::cout << "Create Texture from surface Failed! Error: " << SDL_GetError() <<std::endl;
        }
        else {

            w = loaded->w;
            h = loaded->h;
        }

        SDL_FreeSurface(loaded);
    }

    tex = newTex;

return tex != NULL;
}

void Texture::free() {

    if(tex != NULL) {

        SDL_DestroyTexture(tex);
        tex = NULL;
        w = 0;
        h = 0;
    }
}

void Texture::setColor(Uint8 r, Uint8 g, Uint8 b) {

    SDL_SetTextureColorMod(tex, r, g, b);
}

void Texture::setBlendMode(SDL_BlendMode blend) {

    SDL_SetTextureBlendMode(tex, blend);
}

void Texture::setAlpha(Uint8 alpha) {

    SDL_SetTextureAlphaMod(tex, alpha);
}


void Texture::render(int x, int y, SDL_Rect* clip) {

    SDL_Rect quad = {x, y, w, h};
    if(clip != NULL) {

        quad.w = clip->w;
        quad.h = clip->h;
    }

    SDL_RenderCopy(scr, tex, clip, &quad);
}

int Texture::getW() {

return w;
}

int Texture::getH() {

return h;
}
