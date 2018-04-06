#include "vec2.h"

Vec2::Vec2() : x(0), y(0) {}

Vec2::Vec2(float a, float b) : x(a), y(b) {}

Vec2::Vec2(const Vec2& v) : x(v.x), y(v.y) {}

Vec2 Vec2::operator+(Vec2& v) 
{
	return Vec2(x + v.x, y + v.y);
}

Vec2 Vec2::operator-(Vec2& v) 
{
    return Vec2(x - v.x, y - v.y);
}

Vec2& Vec2::operator+=(Vec2& v) 
{
    x += v.x;
    y += v.y;
    return *this;
}

Vec2& Vec2::operator-=(Vec2& v) 
{
    x -= v.x;
    y -= v.y;
    return *this;
}

Vec2 Vec2::operator+(float s) 
{
    return Vec2(x + s, y + s);
}

Vec2 Vec2::operator-(float s) 
{
    return Vec2(x - s, y - s);
}

Vec2 Vec2::operator*(float s) 
{
    return Vec2(x * s, y * s);
}

Vec2 Vec2::operator/(float s) 
{
    return Vec2(x / s, y / s);
}

Vec2& Vec2::operator+=(float s) 
{
    x += s;
    y += s;
    return *this;
}

Vec2& Vec2::operator-=(float s) 
{
    x -= s;
    y -= s;
    return *this;
}

Vec2& Vec2::operator*=(float s) 
{
    x *= s;
    y *= s;
    return *this;
}

Vec2& Vec2::operator/=(float s) 
{
    x /= s;
    y /= s;
    return *this;
}

void Vec2::Rotate(float deg) 
{
    float theta = deg / 180.0 * M_PI;
    float c = cos(theta);
    float s = sin(theta);
    float tx = x * c - y * s;
    float ty = x * s + y * c;
    x = tx;
    y = ty;
}

Vec2& Vec2::Normalize() 
{
    if (Length() == 0) return *this;
    *this *= (1.0 / Length());
    return *this;
}

float Vec2::Distance(Vec2 v) const 
{
    Vec2 d(v.x - x, v.y - y);
    return d.Length();
}

float Vec2::Length() const 
{
    return std::sqrt(x * x + y * y);
}

void Vec2::Truncate(float length) 
{
    float angle = atan2f(y, x);
    x = length * cos(angle);
    y = length * sin(angle);
}

Vec2 Vec2::Ortho() const 
{
    return Vec2(y, -x);
}

float Vec2::Dot(Vec2 v1, Vec2 v2) 
{
    return v1.x * v2.x + v1.y * v2.y;
}

float Vec2::Cross(Vec2 v1, Vec2 v2) 
{
    return (v1.x * v2.y) - (v1.y * v2.x);
}