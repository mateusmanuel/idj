#include "PenguinBody.h"

#include "Sprite.h"
#include "PenguinCannon.h"
#include "State.h"
#include "Game.h"
#include "InputManager.h"
#include "Collider.h"
#include "Bullet.h"
#include "Camera.h"
#include "Sound.h"
#include "EndState.h"
#include "GameData.h"

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
    State &state = Game::GetInstance().GetCurrentState();

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
        GameObject* penguinDeath = new GameObject();
		penguinDeath->box.x = associated.box.x;
		penguinDeath->box.y = associated.box.y;

		penguinDeath->AddComponent(new Sprite(*penguinDeath, "assets/img/penguindeath.png", 5, 0.5, 2.5));
		Sound* sound = new Sound(*penguinDeath, "assets/audio/boom.wav");
        sound->Play();
        penguinDeath->AddComponent(sound);

        Game::GetInstance().GetCurrentState().AddObject(penguinDeath);

        associated.RequestDelete();
        pcannon.lock()->RequestDelete();
        Camera::Unfollow();
        Camera::pos = Vec2(0,0);

        GameData::playerVictory = false;
        EndState *endState = new EndState();
        Game::GetInstance().Push(endState);
    }
}

void PenguinBody::Render()
{

}

bool PenguinBody::Is(std::string type)
{
    return type == "PenguinBody";
}

void PenguinBody::NotifyCollision(GameObject& other)
{
	Bullet* bullet = (Bullet*)other.GetComponent("Bullet");
	if(bullet != nullptr)
    {
		if(bullet->targetsPlayer) 
        {
			hp -= bullet->GetDamage();
		}
	}
}

Vec2 PenguinBody::Center()
{
    return associated.box.Center();
}