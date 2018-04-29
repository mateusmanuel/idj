#include "Game.h"
#include "Resources.h"
#include "InputManager.h"

Game* Game::instance = nullptr;

Game& Game::GetInstance()
{
    if(instance == nullptr)
    {
        instance = new Game; 
    }

    return *instance;
}

void Game::Init(string title, int width, int height)
{
    
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
    {
        printf("[ERROR] SDL_Init: %s\n", SDL_GetError());
        return;
    }

    int imageFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
    if(IMG_Init(imageFlags) != imageFlags)
    {
        printf("[ERROR] IMG_Init: %s\n", IMG_GetError());
        return;
    }

    int mixFlags = MIX_INIT_OGG | MIX_INIT_MP3;
    if(Mix_Init(mixFlags) != mixFlags)
    {
      printf("[ERROR] Mix_Init: %s\n", Mix_GetError());
      return;
    }

    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
    {
        printf("[ERROR] Mix_OpenAudio: %s\n", Mix_GetError());
        return;
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if(window == nullptr)
    {
        printf("[ERROR] SDL_CreateWindow: %s\n", Mix_GetError());
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr)
    {
        printf("[ERROR] SDL_CreateRenderer: %s\n", SDL_GetError());
        return;
    }

    state = new State();
    dt = 0.f;
    frameStart = SDL_GetTicks();
}

Game::~Game()
{    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();

    delete state;
}

State& Game::GetState()
{
    return *state;
}

SDL_Renderer* Game::GetRenderer()
{
    return renderer;
}

void Game::Run()
{
    while(not state->QuitRequested())
    {
        CalculateDeltaTime();
        state->Render();
        InputManager::GetInstance().Update();
        state->Update(dt);

        SDL_RenderPresent(renderer);

        SDL_Delay(33);
    }

    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
}

void Game::CalculateDeltaTime()
{
    int elapsedTime = SDL_GetTicks();
    dt = (elapsedTime - frameStart)/100.f;
    frameStart = elapsedTime;
}

float Game::GetDeltaTime()
{
    return dt;
}

