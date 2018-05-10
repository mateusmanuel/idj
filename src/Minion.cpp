#include "Minion.h"

#include "Sprite.h"
#include "Bullet.h"
#include "Game.h"

#define SPEED M_PI/4
#define BULLET_DISTANCE 100.f
#define BULLET_DAMAGE 5

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated), alienCenter(alienCenter)
{
    Sprite* minionSprite = new Sprite(associated, "assets/img/minion.png");
    associated.AddComponent(minionSprite);

    std::shared_ptr<GameObject> alienGO(this->alienCenter.lock());
    associated.box.h = minionSprite->GetHeight();
    associated.box.w = minionSprite->GetWidth();
    associated.box.x = alienGO->box.x;
    associated.box.y = alienGO->box.y;

    arc = arcOffsetDeg;
}

void Minion::Start()
{

}

void Minion::Update(float dt)
{
    std::shared_ptr<GameObject> alienGO(alienCenter.lock());
    if(alienGO == nullptr)
    {
        associated.RequestDelete();
        return;
    }

    arc += SPEED;

    Vec2 sourcePos = Vec2(200, 0);
    sourcePos.Rotate(arc);

    sourcePos += alienGO.get()->box.Center();
    associated.box.x = sourcePos.x; 
    associated.box.y = sourcePos.y;
}

void Minion::Render()
{

}

bool Minion::Is(std::string type)
{
    return type == "Minion";
}

void Minion::Shoot(Vec2 target)
{
    GameObject* bulletGO = new GameObject();
    bulletGO->box.x = associated.box.Center().x;
    bulletGO->box.y = associated.box.Center().y;

    Bullet *bullet = new Bullet(*bulletGO, atan((target.y - associated.box.Center().y)/(target.x - associated.box.Center().x)), BULLET_DAMAGE, BULLET_DISTANCE, target.Distance(associated.box.Center()), "assets/img/minionbullet1.png");
    bulletGO->AddComponent(bullet);

    State &state = Game::GetInstance().GetState();
    state.AddObject(bulletGO); 
}