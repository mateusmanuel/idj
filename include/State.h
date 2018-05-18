#ifndef STATE_H
#define STATE_H

#include <vector>
#include <memory>

#include "GameObject.h"
#include "Music.h"

class State
{
    private:
        GameObject *bg;
        GameObject *map;
        Music *music;
        bool quitRequested;
        std::vector<std::shared_ptr<GameObject>> objectArray;
        bool started;

        void Input();
        void AddObject(int mouseX, int mouseY);
        
    public:
        State();
        ~State();

        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();
        void Start();
        std::weak_ptr<GameObject> AddObject(GameObject* go);
        std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
};

#endif