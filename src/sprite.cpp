#include "sprite.h"
#include "game.h"

Sprite::Sprite()
{
    texture = nullptr;
}

Sprite::Sprite(string file)
{
    texture = nullptr;

    Open(file);
}

Sprite::~Sprite()
{
    printf("[DEBUG] Destructor Sprite\n");
    SDL_DestroyTexture(texture);
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

void Sprite::Render(int x, int y)
{
    SDL_Rect destRect = SDL_Rect {x, y, clipRect.w, clipRect.h};
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &destRect);

    printf("[DEBUG] Render Sprite\n");
}

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