#include "Camera.h"

#include "InputManager.h"

GameObject* Camera::focus;
Vec2 Camera::pos;
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
    if(InputManager::GetInstance().IsKeyDown(SDLK_UP))
    {
        Camera::speed.y = dt;
        Camera::pos.y += Camera::speed.y;
    }
    if(InputManager::GetInstance().IsKeyDown(SDLK_DOWN))
    {
        Camera::speed.y = -dt;
        Camera::pos.y += Camera::speed.y;
    }
    if(InputManager::GetInstance().IsKeyDown(SDLK_LEFT))
    {
        Camera::speed.x = dt;
        Camera::pos.x += Camera::speed.x;
    }
    if(InputManager::GetInstance().IsKeyDown(SDLK_RIGHT))
    {
        Camera::speed.x = -dt;
        Camera::pos.x += Camera::speed.x;
    }
}

