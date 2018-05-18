#include "PenguinBody.h"

#include "Sprite.h"
#include "PenguinCannon.h"
#include "State.h"
#include "Game.h"
#include "InputManager.h"
#include "Collider.h"

#define MAX_LINEAR_SPEED 50.f
#define ANGULAR_VELOCITY M_PI/16

PenguinBody* PenguinBody::player;

PenguinBody::PenguinBody(GameObject& associated) : Component(associated)
{
    associated.AddComponent(new Collider(associated));
    
    Sprite* sprite = new Sprite(associated, "assets/img/penguin.png");
    associated.AddComponent(sprite);

    associated.box.h = sprite->GetHeight();
    associated.box.w = sprite->GetWidth();

    player = this;
    hp = 100;
}

PenguinBody::~PenguinBody()
{
    player = nullptr;
}

void PenguinBody::Start()
{
    State &state = Game::GetInstance().GetState();

    GameObject* penguinCannonGO = new GameObject();
    penguinCannonGO->AddComponent(new PenguinCannon(*penguinCannonGO, state.GetObjectPtr(&associated)));


    pcannon = state.AddObject(penguinCannonGO); 
}

void PenguinBody::Update(float dt)
{
    if(InputManager::GetInstance().IsKeyDown(SDLK_w))
    {
        if(linearSpeed < MAX_LINEAR_SPEED)
        {
            linearSpeed += dt * ANGULAR_VELOCITY;
        }
    }

    if(InputManager::GetInstance().IsKeyDown(SDLK_s))
    {
        if(linearSpeed > -MAX_LINEAR_SPEED)
        {
            linearSpeed -= dt * ANGULAR_VELOCITY; 
        }
    }

    if(InputManager::GetInstance().IsKeyDown(SDLK_a))
    {
        angle -= dt;
    }

    if(InputManager::GetInstance().IsKeyDown(SDLK_d))
    {
        angle += dt;
    }

    associated.angleDeg = angle * (180 / M_PI);

    speed.x = linearSpeed * cos(angle);
    speed.y = linearSpeed * sin(angle);

    associated.box.x += speed.x;
    associated.box.y += speed.y;

    if(hp <= 0)
    {
        associated.RequestDelete();
        pcannon.lock()->RequestDelete();
    }
}

void PenguinBody::Render()
{

}

bool PenguinBody::Is(std::string type)
{
    return type == "PenguinBody";
}