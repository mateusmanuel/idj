#include "PenguinCannon.h"

#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "Bullet.h"
#include "Game.h"
#include "State.h"

#define BULLET_SPEED 20
#define BULLET_DAMAGE 5

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody) : Component(associated), pbody(penguinBody)
{
    Sprite* sprite = new Sprite(associated, "assets/img/cubngun.png");
    associated.AddComponent(sprite);

    associated.box.h = sprite->GetHeight();
    associated.box.w = sprite->GetWidth();
}

void PenguinCannon::Start()
{
}

void PenguinCannon::Update(float dt)
{
    if(pbody.lock() == nullptr)
    {
        associated.RequestDelete();
        return;
    }

    associated.box.x = pbody.lock()->box.Center().x;
    associated.box.y = pbody.lock()->box.Center().y;
        
    associated.angleDeg = (180 / M_PI) * atan2((InputManager::GetInstance().GetMouseY() - Camera::pos.y - associated.box.Center().y), (InputManager::GetInstance().GetMouseX() - Camera::pos.x - associated.box.Center().x));

    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON))
    {
        Shoot();
    }
}

void PenguinCannon::Render()
{

}

bool PenguinCannon::Is(std::string type)
{
    return type == "PenguinCannon";
}

void PenguinCannon::Shoot()
{
    Vec2 target = Vec2(InputManager::GetInstance().GetMouseX() - Camera::pos.x, InputManager::GetInstance().GetMouseY() - Camera::pos.y);

    GameObject* bulletGO = new GameObject();
    bulletGO->box.x = associated.box.Center().x;
    bulletGO->box.y = associated.box.Center().y;

    Bullet* bullet = new Bullet(*bulletGO, associated.angleDeg, BULLET_SPEED, BULLET_DAMAGE, associated.box.Center().Distance(target), "assets/img/minionbullet2.png", 3, 1.f);
    bulletGO->AddComponent(bullet);

    State &state = Game::GetInstance().GetState();
    state.AddObject(bulletGO); 
}