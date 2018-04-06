#include "face.h"

#include "sound.h"

Face::Face(GameObject& associated) : Component(associated)
{
    hitpoints = 30;
}

void Face::Damage(int damage)
{
    hitpoints -= damage;

    if(hitpoints <= 0)
    {
        associated.RequestDelete();
        Sound* sound = (Sound *)associated.GetComponent("sound");
        sound->Play();
    }
}

bool Face::Is(std::string type)
{
    return type == "Face";
}

void Face::Render() {}

void Face::Update(float dt) {}