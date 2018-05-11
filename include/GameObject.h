#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <iostream>

#include "Component.h"
#include "Rect.h"

using std::vector;
using std::string;

class GameObject 
{
    private:
        vector<Component*> components;
        bool isDead;
        bool started;
    
    public:
        GameObject();
        ~GameObject();

        void Start();
        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);
        Component* GetComponent(string type);

        Rect box;
        double angleDeg;
};

#endif