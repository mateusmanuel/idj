#include "state.h"

State::State()
{
    quitRequested = false;

    music = new Music("assets/audio/stageState.ogg");
    music->Play(-1);
    
    bg = new Sprite("assets/img/ocean.jpg");
}

State::~State()
{
    delete bg;
    delete music;
}

void State::LoadAssets()
{

}

void State::Update(float dt)
{
    if(SDL_QuitRequested())
    {
        quitRequested = true;
    }
}

void State::Render()
{
    bg->Render(0, 0);
}

bool State::QuitRequested()
{
    return quitRequested;
}