#include "Bullet.h"

#include "Sprite.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite) : Component(associated), damage(damage), distanceLeft(maxDistance)
{
    Sprite* spriteComponent = new Sprite(associated, sprite);
    associated.AddComponent(spriteComponent);

    associated.box.h = spriteComponent->GetHeight();
    associated.box.w = spriteComponent->GetWidth();

    this->speed.x = speed * cos(angle);
    this->speed.x = speed * sin(angle);
}

void Bullet::Update(float dt)
{
    distanceLeft -= speed.Distance(Vec2(speed*dt));

    if(distanceLeft <= 0.f)
    {
        double angle = atan2(associated.box.Center().y, associated.box.Center().x);

        speed.x = cos(angle) * distanceLeft;
        speed.y = sin(angle) * distanceLeft;

        associated.box.x += speed.x;
        associated.box.y += speed.y;

        associated.RequestDelete();
    }
    else
    {
        associated.box.x += speed.x;
        associated.box.y += speed.y;
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