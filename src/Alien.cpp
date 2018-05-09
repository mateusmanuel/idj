#include "Alien.h"

#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"

#define EPS 1

Alien::Alien(GameObject& associated, int nMinions) : Component(associated)
{
    associated.AddComponent(new Sprite(associated, "assets/img/alien.png"));
    
    minionArray.resize(nMinions);

    speed = Vec2();
    hp = 30;
}

void Alien::Start()
{

}

Alien::~Alien()
{
    minionArray.clear();
}

Alien::Action::Action(ActionType type, float x, float y) : type(type)
{
    pos = Vec2(x, y);
}

void Alien::Update(float dt)
{
    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON))
    {
        taskQueue.emplace(Alien::Action(Action::ActionType::SHOOT , InputManager::GetInstance().GetMouseX() - Camera::pos.x,InputManager::GetInstance().GetMouseY() - Camera::pos.y));
    }

    if(InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON))
    {
        taskQueue.emplace(Alien::Action(Action::ActionType::MOVE , InputManager::GetInstance().GetMouseX() - Camera::pos.x,InputManager::GetInstance().GetMouseY() - Camera::pos.y));
    }

    if(not taskQueue.empty())
    {
        if(taskQueue.front().type == Action::ActionType::MOVE)
        {
            bool arrived = taskQueue.front().pos.Distance(associated.box.Center()) <= EPS;

            if(arrived)
            {
                associated.box.x = taskQueue.front().pos.x;
                associated.box.y = taskQueue.front().pos.y;                
                taskQueue.pop();
            }
            else
            {
                double angle = atan2(taskQueue.front().pos.y - associated.box.Center().y, taskQueue.front().pos.x - associated.box.Center().x);

                speed.x = cos(angle) * 5;
                speed.y = sin(angle) * 5;

                associated.box.x += (speed.x * dt);
                associated.box.y += (speed.y * dt);
            }
        }
        else if(taskQueue.front().type == Action::ActionType::SHOOT)
        {
            taskQueue.pop();
        }
    }

    if(hp <= 0)
    {
        associated.RequestDelete();
    }
}

void Alien::Render()
{

}

bool Alien::Is(std::string type)
{
    return type == "Alien";
}