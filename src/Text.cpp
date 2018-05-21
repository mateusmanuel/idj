#include "Text.h"

#include "Resources.h"
#include "Camera.h"
#include "Game.h"

Text::Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, float showTime) : Component(associated), fontFile(fontFile), fontSize(fontSize), style(style), text(text), color(color), showTime(showTime)
{
    font = Resources::GetFont(fontFile, fontSize).get();

    RemakeTexture();
    timer = Timer();
    show = true;
}

Text::~Text()
{
    if(texture != nullptr)
    {
        SDL_DestroyTexture(texture);
    }
}

void Text::Update(float dt)
{
    if(showTime == 0.f)
    {
        show = true;
        return;
    }

    timer.Update(dt);
    if(timer.Get() > showTime)
    {
        show = not show;
        timer.Restart();
    }
}

void Text::Render()
{
    if(texture == nullptr or not show)
    {
        return;
    }

    SDL_Rect destRect = SDL_Rect {associated.box.x - Camera::pos.x, associated.box.y - Camera::pos.y, associated.box.w, associated.box.h};
    SDL_Rect clipRect = destRect;
    clipRect.x = clipRect.y = 0; 
    
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &destRect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
}

void Text::SetText(std::string text)
{
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style)
{
    this->style = style;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize)
{
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::SetFontFile(std::string fontFile)
{
    this->fontFile = fontFile;
    RemakeTexture();
}

void Text::RemakeTexture()
{
    if (texture != nullptr) 
    {
        SDL_DestroyTexture(texture);
    }

    SDL_Surface* surface = nullptr;

    switch (style) 
    {
        case SOLID:
            surface = TTF_RenderText_Solid(font, text.c_str(), color);
            break;
    
        case SHADED:
            surface = TTF_RenderText_Shaded(font, text.c_str(), color, {0, 0, 0, 255});
            break;
    
        case BLENDED:
            surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, associated.box.w);
            break;
    }

    associated.box.h = surface->h;
    associated.box.w = surface->w;

    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
    SDL_FreeSurface(surface);
}

bool Text::Is(std::string type)
{
    return type == "Text";
}