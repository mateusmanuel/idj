#ifndef ALIEN_H
#define ALIEN_H

#include <queue>
#include <vector>
#include <memory>

#include "Component.h"
#include "Vec2.h"
#include "Minion.h"

class Alien : public Component
{
    private:
        class Action 
        {
            public:
                enum ActionType {MOVE, SHOOT};
                
                Action(ActionType type, float x, float y);
                
                ActionType type;
                Vec2 pos;
        };

        Vec2 speed;
        int hp;

        std::queue<Action> taskQueue;
        std::vector<std::weak_ptr<GameObject> > minionArray;

    public:
        Alien(GameObject& associated, int nMinions);
        ~Alien();
        
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);

        Minion* GetClosestMinion(Vec2 pos);
        void NotifyCollision(GameObject& other);
};


#endif