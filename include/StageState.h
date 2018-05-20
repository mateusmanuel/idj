#ifndef STAGESTATE_H
#define STAGESTATE_H

#include "State.h"
#include "Music.h"
#include "TileSet.h"

class StageState : public State
{
    private:
        TileSet* tileSet;
        Music backgroundMusic;

    public:
        StageState();
        ~StageState();
        
        void LoadAssets();
        void Update(float dt);
        void Render();
        
        void Start();
        void Pause();
        void Resume();
};

#endif