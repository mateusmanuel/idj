#ifndef MUSIC_H
#define MUSIC_H

#include <iostream>

#include "SDL2/SDL_mixer.h"

using std::string;

class Music
{
    private:
        Mix_Music* music;

    public:
        Music();
        Music(string file);

        void Play(int times = -1);
        void Stop(int msToStop = 1500);
        void Open(string file); 
        bool IsOpen();
};

#endif