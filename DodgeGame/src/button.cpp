#include "button.h"

Button::Button()
{}
Button::~Button()
{}
void Button::setPosition(int x, int y)
{
    mousePos.x = x;
    mousePos.y = y;
}
bool Button::handleEvent(SDL_Event* e, int BUTTON_WIDTH, int BUTTON_HEIGHT)
{
    bool inside = true;
    if (e -> type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONUP || e->type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState(&x,&y);
        inside = true;
        
        if (x < mousePos.x) inside = false;
        else if (x > mousePos.x + BUTTON_WIDTH) inside = false;
        else if (y < mousePos.y) inside = false;
        else if (y > mousePos.y + BUTTON_HEIGHT) inside = false;
        else inside = true;
    }
    return inside;
}