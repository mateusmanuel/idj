#include "Sprite.h"
#include "Game.h"
#include "Resources.h"

Sprite::Sprite(GameObject& associated) : Component(associated)
{
    texture = nullptr;
    scale = Vec2(1.f, 1.f);
}

Sprite::Sprite(GameObject& associated, string file) : Sprite(associated)
{
    Open(file);
}

Sprite::~Sprite()
{
}

void Sprite::Open(string file)
{
    if(texture != nullptr)
    {
        SDL_DestroyTexture(texture);
    }

    texture = Resources::GetImage(file);

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
    SDL_Rect destRect = SDL_Rect {(int)x, (int)y, clipRect.w * scale.x, clipRect.h * scale.y};
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &destRect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
}

bool Sprite::Is(std::string type)
{
    return type == "Sprite";
}

void Sprite::Update(float dt) 
{

}

int Sprite::GetWidth()
{
    return width * (int)scale.y;
}

int Sprite::GetHeight()
{
    return height * (int)scale.y;
}

bool Sprite::IsOpen()
{
    return texture != nullptr;
}

void Sprite::Start() 
{
    
}

void Sprite::SetScaleX(float scaleX, float scaleY)
{
    if(scaleX != 0.f)
    {
        scale.x = scaleX;
    }

    if(scaleY != 0.f)
    {
        scale.y = scaleY;
    }

    associated.box.h = GetHeight();
    associated.box.w = GetWidth();
}