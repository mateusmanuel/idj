#include "Rect.h"

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

float Area(int x1, int y1, int x2, int y2, int x3, int y3);
        
bool Rect::Contains(Vec2 v)
{
    float A = Area(x, y, x+w, y, x, y+h) + 
              Area(x, y, x+w, y+h, x, y+h);
 
    float A1 = Area(v.x, v.y, x, y, x+w, y);
    float A2 = Area(v.x, v.y, x+w, y, x, y+h);
    float A3 = Area(v.x, v.y, x, y+h, x+w, y+h);
    float A4 = Area(v.x, v.y, x, y, x+w, y+h);
 
    return (A >= A1 + A2 + A3 + A4);
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

float Area(int x1, int y1, int x2, int y2, int x3, int y3)
{
    return abs((x1 * (y2 - y3) + x2 * (y3 - y1) + 
                x3 * (y1 - y2)) / 2.0);
}