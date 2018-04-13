#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(GameObject& associated) : Component(associated)
{
    texture = nullptr;
}

Sprite::Sprite(GameObject& associated, string file) : Sprite(associated)
{
    Open(file);
}

Sprite::~Sprite()
{
    if(IsOpen())
    {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(string file)
{
    if(texture != nullptr)
    {
        SDL_DestroyTexture(texture);
    }

    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if(texture == nullptr)
    {
        printf("[ERROR] IMG_LoadTexture: %s\n", SDL_GetError());
        return;
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h)
{
    clipRect = SDL_Rect {x, y, w, h};
}

void Sprite::Render()
{
    //SDL_Rect destRect = SDL_Rect {(int)associated.box.x, (int)associated.box.y, clipRect.w, clipRect.h};
    //SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &destRect);
    Render(associated.box.x, associated.box.y);
}

void Sprite::Render(float x, float y)
{
    SDL_Rect destRect = SDL_Rect {(int)x, (int)y, clipRect.w, clipRect.h};
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &destRect);
}

bool Sprite::Is(std::string type)
{
    return type == "Sprite";
}

void Sprite::Update(float dt) {}

int Sprite::GetWidth()
{
    return width;
}

int Sprite::GetHeight()
{
    return height;
}

bool Sprite::IsOpen()
{
    return texture != nullptr;
}