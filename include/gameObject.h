#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <iostream>

#include "component.h"
#include "rect.h"

using std::vector;
using std::string;

class GameObject 
{
    private:
        vector<Component*> components;
        bool isDead;
    
    public:
        GameObject();
        ~GameObject();

        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);
        Component* GetComponent(string type);

        Rect box;
};

#endif