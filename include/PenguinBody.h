#ifndef PENGUINBODY_H
#define PENGUINBODY_H

#include <memory>

#include "Component.h"
#include "Vec2.h"

class PenguinBody : public Component
{
    private:
        std::weak_ptr<GameObject> pcannon; 
        Vec2 speed;
        float linearSpeed;
        float angle;
        int hp;
    
    public:
        static PenguinBody* player;

        PenguinBody(GameObject& associated);
        ~PenguinBody();

        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
};

#endif
