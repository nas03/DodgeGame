#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>

class Music
{
public:
    Music();
    ~Music();
    void playMusic(const char* path);
};