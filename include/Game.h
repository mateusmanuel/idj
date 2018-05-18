#ifndef GAME_H
#define GAME_H

#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

#include "State.h"

using std::string;

class Game
{
  private:
    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;
    int frameStart;
    float dt;
    void CalculateDeltaTime();

    int width;
		int height;

  public:
    ~Game();

    void Init(string title, int width, int height);
    static Game& GetInstance();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    float GetDeltaTime();

    int GetHeight();
    int GetWidth();
};

#endif
