#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Button
{
public:
    Button();
    ~Button();
    void setPosition(int x, int y);
    bool handleEvent(SDL_Event* e, int BUTTON_WIDTH, int BUTTON_HEIGHT);
private:
    SDL_Point mousePos;
};