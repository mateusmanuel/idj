#include "Bullet.h"

#include "Sprite.h"
#include "Collider.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite, int frameCount, float frameTime, bool targetsPlayer) : Component(associated), damage(damage), distanceLeft(maxDistance), targetsPlayer(targetsPlayer)
{
    associated.AddComponent(new Collider(associated));

    Sprite* spriteComponent = new Sprite(associated, sprite, frameCount, frameTime);
    associated.AddComponent(spriteComponent);

    associated.box.h = spriteComponent->GetHeight();
    associated.box.w = spriteComponent->GetWidth();
    associated.angleDeg = angle * (180 / M_PI);

    this->speed.x = speed * cos(angle);
    this->speed.y = speed * sin(angle);
}

void Bullet::Update(float dt)
{
    distanceLeft -= Vec2(speed*dt).Length();

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

void Bullet::NotifyCollision (GameObject& other)
{
	if ((other.GetComponent("Alien") && not targetsPlayer)	|| (other.GetComponent("PenguinBody") && targetsPlayer)) 
    {
		associated.RequestDelete();
	}
}
