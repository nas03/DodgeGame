#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>


class Text
{
public:
    Text(SDL_Renderer* renderer);
    ~Text();
    void drawText(std::string text, int x, int y, int fontSize);
private:
    SDL_Renderer* renderer;
};