#include "music.h"

Music::Music()
{
    music = nullptr;
}

Music::Music(string file)
{
    music = nullptr;

    Open(file);
}

void Music::Play(int times)
{
    Mix_PlayMusic(music, times);
}

void Music::Stop(int msToStop)
{
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(string file)
{
    music = Mix_LoadMUS(file.c_str());
    if(music == nullptr)
    {
        printf("[ERROR] Mix_LoadMUS: %s\n", SDL_GetError());
        return;
    }
}

bool Music::IsOpen()
{
    return music != nullptr;
}

Music::~Music()
{
    Mix_FreeMusic(music);
}

