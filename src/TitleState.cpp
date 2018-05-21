#include "TitleState.h"

#include "GameObject.h"
#include "Sprite.h"
#include "InputManager.h"
#include "StageState.h"
#include "Game.h"
#include "Camera.h"
#include "Text.h"

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

    GameObject* titleMessage = new GameObject();
    titleMessage->AddComponent(new Text(*titleMessage, "assets/font/Call me maybe.ttf", 80, Text::TextStyle::BLENDED, "Press Space to begin", {0, 0, 0, 255}, 3.0));
    titleMessage->box.y = Game::GetInstance().GetHeight()/1.3;
    titleMessage->box.x = Game::GetInstance().GetWidth()/6;
    objectArray.emplace_back(titleMessage);
}

void TitleState::Update(float dt)
{
    if(InputManager::GetInstance().KeyPress(SDLK_ESCAPE) || InputManager::GetInstance().QuitRequested())
    {
        popRequested = true;
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