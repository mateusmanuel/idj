#ifndef STATE_H
#define STATE_H

#include "gameObject.h"
#include "music.h"

class State
{
    private:
        GameObject *bg;
        Music *music;
        bool quitRequested;

    public:
        State();
        ~State();

        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();
};

#endif