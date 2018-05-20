#include "Camera.h"

#include "InputManager.h"
#include "Game.h"

GameObject* Camera::focus = nullptr;
Vec2 Camera::pos(0, 0);
Vec2 Camera::speed;

void Camera::Follow(GameObject* newFocus)
{
    focus = newFocus;
}

void Camera::Unfollow()
{
    focus = nullptr;
}

void Camera::Update(float dt)
{
    if(focus != nullptr)
    {
        Camera::pos.x = focus->box.x - (Game::GetInstance().GetWidth()/2);
        Camera::pos.y = focus->box.y - (Game::GetInstance().GetHeight()/2);
    }
    else
    {
        if(InputManager::GetInstance().IsKeyDown(SDLK_UP))
        {
            Camera::speed.y = -dt;
            Camera::pos.y += Camera::speed.y;
        }
        if(InputManager::GetInstance().IsKeyDown(SDLK_DOWN))
        {
            Camera::speed.y = dt;
            Camera::pos.y += Camera::speed.y;
        }
        if(InputManager::GetInstance().IsKeyDown(SDLK_LEFT))
        {
            Camera::speed.x = -dt;
            Camera::pos.x += Camera::speed.x;
        }
        if(InputManager::GetInstance().IsKeyDown(SDLK_RIGHT))
        {
            Camera::speed.x = dt;
            Camera::pos.x += Camera::speed.x;
        }
    }
}

