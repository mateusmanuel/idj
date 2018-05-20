#ifndef PENGUINCANNON_H
#define PENGUINCANNON_H

#include <memory>

#include "Component.h"
#include "Timer.h"

class PenguinCannon : public Component
{
    private:
        std::weak_ptr<GameObject> pbody;
        float angle;
        Timer* timer;

    public:
        PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody);

        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void Shoot();
};

#endif