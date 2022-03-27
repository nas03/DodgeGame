#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "game_object.h"
class Menu : public GameObject
{
public:
    Menu(SDL_Renderer*renderer, const char* path);
    ~Menu();
    void Render();
private:
    SDL_Texture* texture;
};