#ifndef STATE_H
#define STATE_H

#include "sprite.h"
#include "music.h"

class State
{
    private:
        Sprite bg;
        Music music;
        bool quitRequested;

    public:
        State();

        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();
};

#endif