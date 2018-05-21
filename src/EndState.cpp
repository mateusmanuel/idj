#include "EndState.h"

#include "GameData.h"
#include "Sprite.h"
#include "InputManager.h"
#include "StageState.h"
#include "Game.h"

EndState::EndState()
{
    GameObject* bg = new GameObject();
    if(GameData::playerVictory) 
    {
        bg->AddComponent(new Sprite(*bg, "assets/img/win.jpg"));
        backgroundMusic = Music("assets/audio/endStateWin.ogg");
    } 
    else 
    {
        bg->AddComponent(new Sprite(*bg, "assets/img/lose.jpg"));
        backgroundMusic = Music("assets/audio/endStateLose.ogg");
    }
    backgroundMusic.Play(1);

    objectArray.emplace_back(bg);
}

void EndState::Start()
{
    LoadAssets();

    StartArray();
}

void EndState::Update(float dt)
{ 
    if(InputManager::GetInstance().KeyPress(SDLK_ESCAPE) || InputManager::GetInstance().QuitRequested())
    {
		quitRequested = true;
	}

    if(InputManager::GetInstance().KeyPress(SDLK_SPACE))
    {
        popRequested = true;
		StageState *stageState = new StageState();
        Game::GetInstance().Push(stageState);
	}

    UpdateArray(dt); 
}

void EndState::Render()
{ 
    RenderArray(); 
}

void EndState::LoadAssets()
{
    
}

void EndState::Pause()
{

}

void EndState::Resume()
{

}

EndState::~EndState()
{

}