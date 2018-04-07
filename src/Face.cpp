#include "Face.h"

#include "Sound.h"

Face::Face(GameObject& associated) : Component(associated)
{
    hitpoints = 30;
    delayDeathTime = 25;
}

void Face::Damage(int damage)
{
    hitpoints -= damage;

    if(hitpoints <= 0)
    {
        Sound* sound = (Sound *)associated.GetComponent("Sound");
        sound->Play();
    }
}

bool Face::Is(std::string type)
{
    return type == "Face";
}

void Face::Render() {}

void Face::Update(float dt) 
{
    if(hitpoints <= 0)
    {
        delayDeathTime--;
    }
    if(delayDeathTime == 0)
    {
        associated.RequestDelete();
    }
}