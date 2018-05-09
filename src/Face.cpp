#include "Face.h"

#include "Sound.h"
#include "InputManager.h"
#include "Camera.h"
#include "Sprite.h"

Face::Face(GameObject& associated) : Component(associated)
{
    hitpoints = 30;
    delayDeathTime = 25;
}

void Face::Damage(int damage)
{
    hitpoints -= damage;

    if(hitpoints <= 0)
    {
        Sound* sound = (Sound *)associated.GetComponent("Sound");
        sound->Play();
    }
}

bool Face::Is(std::string type)
{
    return type == "Face";
}

void Face::Render() 
{
    if(InputManager::GetInstance().IsKeyDown(SDLK_UP))
    {
        associated.box.y += fabs(Camera::speed.y)*64.f;
    }
    if(InputManager::GetInstance().IsKeyDown(SDLK_DOWN))
    {
        associated.box.y -= fabs(Camera::speed.y)*64.f;
    }
    if(InputManager::GetInstance().IsKeyDown(SDLK_LEFT))
    {
        associated.box.x += fabs(Camera::speed.x)*64.f;
    }
    if(InputManager::GetInstance().IsKeyDown(SDLK_RIGHT))
    {
        associated.box.x -= fabs(Camera::speed.x)*64.f;
    }
}

void Face::Update(float dt) 
{
    if(hitpoints <= 0)
    {
        delayDeathTime--;
    }
    if(delayDeathTime == 0)
    {
        associated.RequestDelete();
    }

    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) 
    {
    	if(associated.box.Contains( Vec2((float)InputManager::GetInstance().GetMouseX(), (float)InputManager::GetInstance().GetMouseY()))) 
        {
			this->Damage(std::rand() % 10 + 10);
		}
    }
}

void Face::Start()
{
}