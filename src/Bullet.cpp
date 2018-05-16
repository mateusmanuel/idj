#include "Bullet.h"

#include "Sprite.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite, int frameCount, float frameTime) : Component(associated), damage(damage), distanceLeft(maxDistance)
{
    Sprite* spriteComponent = new Sprite(associated, sprite, frameCount, frameTime);
    associated.AddComponent(spriteComponent);

    associated.box.h = spriteComponent->GetHeight();
    associated.box.w = spriteComponent->GetWidth();
    associated.angleDeg = angle;

    this->speed.x = speed * cos(angle);
    this->speed.y = speed * sin(angle);
}

void Bullet::Update(float dt)
{
    distanceLeft -= speed.Distance(Vec2(speed*dt));

    if(distanceLeft <= 0.f)
    {
        associated.RequestDelete();
    }
    else
    {
        associated.box.x += (speed.x * dt);
        associated.box.y += (speed.y * dt);
    }
}

void Bullet::Start()
{

}

void Bullet::Render()
{

}

bool Bullet::Is(std::string type)
{
    return type == "Bullet";
}

int Bullet::GetDamage()
{
    return damage;
}