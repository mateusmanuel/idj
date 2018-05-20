#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

Sprite::Sprite(GameObject& associated) : Component(associated)
{
    texture = nullptr;
    scale = Vec2(1.f, 1.f);
}

Sprite::Sprite(GameObject& associated, std::string file, int frameCount, float frameTime, float secondsToSelfDestruct) : Sprite(associated)
{
    Open(file);

    SetFrameCount(frameCount);
    SetFrameTime(frameTime);
    
    timeElapsed = 0.f;
    currentFrame = 0;
    this->secondsToSelfDestruct = secondsToSelfDestruct;
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
    Render(associated.box.x - Camera::pos.x, associated.box.y - Camera::pos.y);
}

void Sprite::Render(float x, float y)
{
    //printf("Angle: %lf\n", associated.angleDeg);
    SDL_Rect destRect = SDL_Rect {(int)x, (int)y, (int)(clipRect.w * scale.x), (int)(clipRect.h * scale.y)};
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &destRect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
}

bool Sprite::Is(std::string type)
{
    return type == "Sprite";
}

void Sprite::Update(float dt) 
{
    if(secondsToSelfDestruct > 0)
    {
		selfDestructCount.Update(dt);

		if(selfDestructCount.Get() >= secondsToSelfDestruct)
        {
			associated.RequestDelete();
		}
	}

    timeElapsed += dt;

    if(timeElapsed > frameTime)
    {
        SetFrame(currentFrame + 1);
    }

    if(frameCount == currentFrame)
    {
        SetFrame(0);
    }
}

int Sprite::GetWidth()
{
    return (width * (int)scale.x) / frameCount;
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
    if(scaleX > 0.f)
    {
        scale.x = scaleX;
    }

    if(scaleY > 0.f)
    {
        scale.y = scaleY;
    }

    associated.box.h = GetHeight();
    associated.box.w = GetWidth();
}

void Sprite::SetFrame(int frame)
{
    SetClip(frame * GetWidth(), 0, GetWidth(), GetHeight());
    currentFrame = frame;
}

void Sprite::SetFrameCount(int frameCount)
{
    this->frameCount = frameCount;

    SetFrame(0);
    associated.box.w = GetWidth();
}

void Sprite::SetFrameTime(float frameTime)
{
    this->frameTime = frameTime;
}