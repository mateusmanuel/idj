#include "TitleState.h"

#include "GameObject.h"
#include "Sprite.h"
#include "InputManager.h"
#include "StageState.h"
#include "Game.h"
#include "Camera.h"

TitleState::TitleState()
{
    GameObject* title = new GameObject();
    Sprite *titleSprite = new Sprite(*title,"assets/img/title.jpg");
    title->AddComponent(titleSprite);
    title->box.w = titleSprite->GetWidth();
    title->box.h = titleSprite->GetHeight();
    title->box.x = title->box.y = 0;

    objectArray.emplace_back(title);

    Camera::Unfollow();
    Camera::pos = Vec2(0, 0);
}

void TitleState::Update(float dt)
{
    if(InputManager::GetInstance().KeyPress(SDLK_ESCAPE) || InputManager::GetInstance().QuitRequested())
    {
		quitRequested = true;
	}

    if(InputManager::GetInstance().KeyPress(SDLK_SPACE))
    {
		StageState *stageState = new StageState();
        Game::GetInstance().Push(stageState);
	}

    UpdateArray(dt);
}

TitleState::~TitleState()
{

}

void TitleState::LoadAssets()
{

}

void TitleState::Render()
{
    RenderArray();
}

void TitleState::Start()
{
    LoadAssets();

    StartArray();
}

void TitleState::Pause()
{
    
}

void TitleState::Resume()
{
    
}