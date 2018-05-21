#ifndef ALIEN_H
#define ALIEN_H

#include <queue>
#include <vector>
#include <memory>

#include "Component.h"
#include "Vec2.h"
#include "Minion.h"
#include "Timer.h"

class Alien : public Component
{
    private:
        enum AlienState {MOVING, RESTING};

        Vec2 speed;
        int hp;

        std::vector<std::weak_ptr<GameObject> > minionArray;

        AlienState state;
        Timer restTimer;
        Vec2 destination;
        float timeOffset;

    public:
        Alien(GameObject& associated, int nMinions, float timeOffset = 0.f);
        ~Alien();
        
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);

        Minion* GetClosestMinion(Vec2 pos);
        void NotifyCollision(GameObject& other);

        static int alienCount;
};


#endif