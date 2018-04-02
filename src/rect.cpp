#include "rect.h"

#include <algorithm>

Rect::Rect():x(0), y(0), w(0), h(0) {}

Rect::Rect(float a, float b, float c, float d) : x(a), y(b), w(c), h(d) {}

Rect::Rect(const Rect& r) : x(r.x), y(r.y), w(r.w), h(r.h) {}

Vec2& Rect::Center()
{
    float minX = std::min(x, (x + w));
    float maxX = std::max(x, (x + w));
    float minY = std::min(y, (y + h));
    float maxY = std::max(y, (y + h));

    return *(new Vec2((minX + maxX)/2.0, (minY + maxY)/2.0));
}
        
bool Rect::Contains(Vec2 v)
{
    float minX = std::min(v.x, (v.x + w));
    float maxX = std::max(v.x, (v.x + w));
    float minY = std::min(v.y, (v.y + h));
    float maxY = std::max(v.y, (v.y + h));

    return (x >= minX) && (x < maxX) && (y >= minY) && (y < maxY);
}

bool Rect::Intersects(Rect r)
{
    Rect i;
    return Intersects(r, i);
}

bool Rect::Intersects(Rect r, Rect i) 
{
    float r1MinX = std::min(x, (x + w));
    float r1MaxX = std::max(x, (x + w));
    float r1MinY = std::min(y, (y + h));
    float r1MaxY = std::max(y, (y + h));

    float r2MinX = std::min(r.x, (r.x + r.w));
    float r2MaxX = std::max(r.x, (r.x + r.w));
    float r2MinY = std::min(r.y, (r.y + r.h));
    float r2MaxY = std::max(r.y, (r.y + r.h));

    float interLeft = std::max(r1MinX, r2MinX);
    float interTop = std::max(r1MinY, r2MinY);
    float interRight = std::min(r1MaxX, r2MaxX);
    float interBottom = std::min(r1MaxY, r2MaxY);

    if ((interLeft < interRight) && (interTop < interBottom))
    {
        i = Rect(interLeft, interTop, interRight - interLeft, interBottom - interTop);
        return true;
    }
    else
    {
        i = Rect(0, 0, 0, 0);
        return false;
    }
}
