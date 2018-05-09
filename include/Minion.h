#ifndef MINION_H
#define MINION_H

#include <memory>

#include "Component.h"
#include "Vec2.h"

class Minion : public Component
{
    private:
        float arc;
        std::weak_ptr<GameObject> alienCenter;

    public:
        Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);

        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void Shoot(Vec2 target);
};

#endif