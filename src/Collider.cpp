#include "Collider.h"
#include "GameObject.h"

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) : Component(associated), scale(scale), offset(offset)
{

}

void Collider::Start()
{

}

void Collider::Update(float dt)
{
    box.w = associated.box.w * scale.x;
	box.h = associated.box.h * scale.y;

	offset.Rotate(associated.angleDeg * (180 / M_PI));
	box.x = associated.box.Center().x + offset.x - box.w / 2;
    box.y = associated.box.Center().y + offset.y - box.h / 2;    
}

void Collider::Render()
{

}

bool Collider::Is(std::string type)
{
    return type == "Collider";
}

void Collider::SetScale(Vec2 scale)
{
    this->scale = scale;
}
        
void Collider::SetOffset(Vec2 offset)
{
    this->offset = offset;
}