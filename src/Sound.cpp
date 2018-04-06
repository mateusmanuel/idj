#include "Sound.h"

Sound::Sound(GameObject& associated) : Component(associated)
{
    chunk = nullptr;
}

Sound::Sound(GameObject& associated, std::string file) : Sound(associated)
{
    Open(file);
}

void Sound::Play(int times)
{
    channel = Mix_PlayChannel(-1, chunk, times);
}

void Sound::Stop()
{
    if(chunk != nullptr)
        Mix_HaltChannel(channel);
}

void Sound::Open(std::string file)
{
    chunk = Mix_LoadWAV(file.c_str());
    if(chunk == nullptr)
    {
        printf("[ERROR] Mix_LoadWAV: %s\n", SDL_GetError());
        return;
    }
}

Sound::~Sound()
{
    if(chunk != nullptr)
        Mix_FreeChunk(chunk);
}

bool Sound::Is(std::string type)
{
    return type == "Sound";
}

void Sound::Render() {}

void Sound::Update(float dt) {}