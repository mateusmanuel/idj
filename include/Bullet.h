#ifndef BULLET_H
#define BULLET_H

#include "Component.h"
#include "Vec2.h"

class Bullet : public Component
{
    private:
        Vec2 speed;
        float distanceLeft;
        int damage;

    public:
        Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite);
        
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        int GetDamage();

};

#endif