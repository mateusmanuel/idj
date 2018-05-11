#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>

#include "SDL2/SDL.h"

#include "Component.h"
#include "GameObject.h"

using std::string;

class Sprite : public Component
{
    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;
        Vec2 scale;

    public:
        Sprite(GameObject& associated);
        Sprite(GameObject& associated, string file);
        ~Sprite();

        void Open(string file);
        void SetClip(int x, int y, int w, int h);
        int GetWidth();
        int GetHeight();
        bool IsOpen();

        void SetScaleX(float scaleX, float scaleY);
        Vec2 GetScale();

        void Start();
        void Update(float dt);
        void Render();
        void Render(float x, float y);
        bool Is(string type);
};

#endif