#include "Timer.h"

Timer::Timer()
{
    time = 0.f;
}

void Timer::Update(float dt)
{
    time += dt;
}

void Timer::Restart()
{
    time = 0.f;
}

float Timer::Get()
{
    return time;
}