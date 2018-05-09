#ifndef CAMERAFOLLOWER_H
#define CAMERAFOLLOWER_H

#include <iostream>

#include "Component.h"
#include "GameObject.h"

class CameraFollower : public Component
{
    public:
        CameraFollower (GameObject& go);

        void Start();
        void Update (float dt);
        void Render ();
        bool Is (std::string type);
};

#endif
