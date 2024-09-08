/*************************************************************************************/
/* TODO:
 Revisit this commit to refactor this class.

commit 17d660aec39cfed5eb945c955f286a02e9876bc5 (HEAD -> tutorial, origin/tutorial)
Author: david cramer <dontcallmebrownie@gmail.com>
Date:   Sat Sep 7 19:51:58 2024 -0500

    ***AND THEN REVISIT THE COMMIT IMMEDIATELY AFTER WHICH WILL CONTAIN THIS NOTE***

Note because I'll def forget the solution:
    moving the sprite sheet and texture into the class and use dot notation to load
    the assets in will work, if you want to get fancy use a setter func to load it

                ***DO THIS BEFORE MOVING ON TO WRITE THE PONG GAME***
*/
/*************************************************************************************/

/*

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

*/
