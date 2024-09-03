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

void Texture::render(int x, int y) {

    SDL_Rect quad = {x, y, w, h};
    SDL_RenderCopy(scr, tex, NULL, &quad);
}

int Texture::getW() {

return w;
}

int Texture::getH() {

return h;
}
