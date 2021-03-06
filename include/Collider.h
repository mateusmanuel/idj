#ifndef COLLIDER_H
#define COLLIDER_H

#include "Component.h"
#include "Vec2.h"
#include "Rect.h"

class Collider : public Component
{
    private:
        Vec2 scale;
        Vec2 offset;

    public:
        Collider(GameObject& associated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0}); 
        Rect box;

        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
    
        void SetScale(Vec2 scale); 
        void SetOffset(Vec2 offset);
};

#endif