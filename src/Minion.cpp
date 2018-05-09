#include "Minion.h"

#include "Sprite.h"

#define SPEED M_PI/4

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