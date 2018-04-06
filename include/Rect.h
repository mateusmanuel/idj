#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

class Rect 
{
    public:
        float x, y, w, h;

        Rect();
        Rect(float x, float y, float w, float h);
        Rect(const Rect& r);

        Vec2& Center();
        bool Contains(Vec2 v);
        bool Intersects(Rect r);
        bool Intersects(Rect r, Rect i);
};

#endif
