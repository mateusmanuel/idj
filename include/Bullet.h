#ifndef BULLET_H
#define BULLET_H

#include "Component.h"
#include "Vec2.h"

class Bullet : public Component
{
    private:
        Vec2 speed;
        int damage;
        float distanceLeft;

    public:
        Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite, int frameCount, float frameTime, bool targetsPlayer);
        
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        int GetDamage();

        void NotifyCollision (GameObject& other);

        bool targetsPlayer;
};

#endif