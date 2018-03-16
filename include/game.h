#ifndef GAME_H
#define GAME_H

#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

#include "state.h"

using std::string;

class Game
{
  private:
    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;

  public:
    ~Game();

    void Init(string title, int width, int height);
    static Game& GetInstance();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();

};

#endif
