#include "music.h"

Music::Music()
{}
Music::~Music()
{}

void Music::playMusic(const char* path)
{
    Mix_Chunk* musicChunk = Mix_LoadWAV(path);
    Mix_VolumeChunk(musicChunk, 20);
	Mix_PlayChannel(-1, musicChunk, 0);
}