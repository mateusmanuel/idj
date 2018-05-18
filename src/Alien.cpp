#include "Alien.h"

#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "Game.h"
#include "Minion.h"

#define EPS 1
#define SPEED 5

Alien::Alien(GameObject& associated, int nMinions) : Component(associated)
{
    Sprite* alienSprite = new Sprite(associated, "assets/img/alien.png");
    associated.AddComponent(alienSprite);
    
    associated.box.h = alienSprite->GetHeight();
    associated.box.w = alienSprite->GetHeight();

    minionArray.resize(nMinions);

    speed = Vec2(100, 100);
    hp = 30;
}

void Alien::Start()
{  
    State &state = Game::GetInstance().GetState();

    std::weak_ptr<GameObject> alienWeakPtr(state.GetObjectPtr(&associated));
    for(int i = 0; i < minionArray.size(); ++i)
    {
        GameObject* minionGO = new GameObject();
        Minion* minion = new Minion(*minionGO, alienWeakPtr, i * 360.0/minionArray.size());
        minionGO->AddComponent(minion);
        minionArray[i] = state.AddObject(minionGO);
    }
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
                associated.box.x = taskQueue.front().pos.x - associated.box.h/2;
                associated.box.y = taskQueue.front().pos.y - associated.box.w/2;
                taskQueue.pop();
            }
            else
            {
                double angle = atan2(taskQueue.front().pos.y - associated.box.Center().y, taskQueue.front().pos.x - associated.box.Center().x);

                speed.x = cos(angle) * SPEED;
                speed.y = sin(angle) * SPEED;

                associated.box.x += (speed.x * dt);
                associated.box.y += (speed.y * dt);
            }
        }
        else if(taskQueue.front().type == Action::ActionType::SHOOT)
        {
            Minion* minion = GetClosestMinion(taskQueue.front().pos);
            minion->Shoot(taskQueue.front().pos);
            
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
    associated.angleDeg -= 0.25;
}

bool Alien::Is(std::string type)
{
    return type == "Alien";
}

Minion* Alien::GetClosestMinion(Vec2 pos)
{

    double minDist = 1e6;
    GameObject* minionGOClose;

    for(int i = 0; i < minionArray.size(); i++){
        GameObject* minionGo = minionArray[i].lock().get();
        
        double dist = minionGo->box.Center().Distance(pos);
        
        if(dist < minDist){
            minionGOClose = minionGo;
            minDist = dist;
        }
    }

    return (Minion*)minionGOClose->GetComponent("Minion");
}