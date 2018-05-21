#include "Music.h"
#include "Resources.h"

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
    Mix_PlayMusic(music.get(), times);
}

void Music::Stop(int msToStop)
{
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(string file)
{
    music = Resources::GetMusic(file);
}

bool Music::IsOpen()
{
    return music != nullptr;
}

Music::~Music()
{
    
}

