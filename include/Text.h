#ifndef TEXT_H
#define TEXT_H

#include "SDL2/SDL_ttf.h"

#include "Component.h"
#include "Timer.h"

class Text : public Component
{
    public:
        enum TextStyle {SOLID, SHADED, BLENDED};
        
    private:
        TTF_Font* font;
        SDL_Texture* texture;
        std::string text;
        TextStyle style;
        std::string fontFile;
        int fontSize;
        SDL_Color color;
        
        Timer timer;
        bool show;
        float showTime;

    public:
        Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, float showTime = 0.f);
        ~Text();

        void Update(float dt);
        void Render();
        bool Is(std::string type);

        void SetText(std::string text);
        void SetColor(SDL_Color color);
        void SetStyle(TextStyle style);
        void SetFontFile(std::string fontFile);
        void SetFontSize(int fontSize);
        void SetShowTime(int showTime);

        void RemakeTexture();
};

#endif