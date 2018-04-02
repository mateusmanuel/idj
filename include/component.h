#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>

using std::string;

class GameObject;

class Component
{
    protected:
        GameObject& associated;

    public:
        Component(GameObject& associated) : associated(associated) {}
        virtual ~Component() {}

        void virtual Update(float dt) = 0;
        void virtual Render() = 0;
        bool virtual Is(string type) = 0;
};

#endif