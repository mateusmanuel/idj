#include "SDL2/SDL.h"

#include "state.h"
#include "sprite.h"

State::State()
{
    quitRequested = false;

    music = new Music("assets/audio/stageState.ogg");
    music->Play(-1);
        
    bg = new GameObject();
    bg->AddComponent(new Sprite(*bg, "assets/img/ocean.jpg"));
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
    bg->Render();
}

bool State::QuitRequested()
{
    return quitRequested;
}