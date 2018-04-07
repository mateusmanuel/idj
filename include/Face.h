#ifndef FACE_H
#define FACE_H

#include <iostream>

#include "GameObject.h"
#include "Component.h"

using std::string;

class Face : public Component
{
    private:
        int hitpoints;
        int delayDeathTime;
    
    public:
        Face(GameObject& associated);

        void Damage(int damage);

        void Update(float dt);
        void Render();
        bool Is(string type);
};

#endif