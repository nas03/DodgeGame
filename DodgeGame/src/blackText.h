#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>


class BlackText
{
public:
    BlackText(SDL_Renderer* renderer);
    void drawText(std::string text, int x, int y, int fontSize);
private:
    SDL_Renderer* renderer;
};