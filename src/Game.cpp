#include "Game.h"
#include "Resources.h"
#include "InputManager.h"
#include "GameData.h"

Game* Game::instance = nullptr;
bool GameData::playerVictory = false;

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
    this->height = height;
    this->width = width;

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

    if(TTF_Init() != 0)
    {
        printf("[ERROR] TTF_Init: %s\n", SDL_GetError());
        return;   
    }

    storedState = nullptr;
    dt = 0.f;
    frameStart = SDL_GetTicks();
}

Game::~Game()
{    
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();

    if(storedState != nullptr)
    {
        delete storedState;
    }

    while(not stateStack.empty())
    {
        stateStack.pop();
    }

    Resources::ClearSounds();
    Resources::ClearMusics();
    Resources::ClearImages(); 
}

State& Game::GetCurrentState()
{
    return *stateStack.top();
}

SDL_Renderer* Game::GetRenderer()
{
    return renderer;
}

void Game::Push(State* state)
{
    storedState = state;
}

void Game::Run()
{
    if(storedState == nullptr)
    {
        return;
    }
    
    stateStack.push((std::unique_ptr<State>)storedState);

    while(not stateStack.empty() && not stateStack.top()->QuitRequested())
    {
        if(stateStack.top()->PopRequested())
        {
            stateStack.pop();
            if(not stateStack.empty())
            {
                stateStack.top()->Resume();
            }
        }

        if(stateStack.empty())
            break;

        if(storedState != nullptr)
        {
            stateStack.top()->Pause();
            stateStack.push((std::unique_ptr<State>)storedState);
            stateStack.top()->Start();
            storedState = nullptr;
        }
        
        CalculateDeltaTime();
        stateStack.top()->Render();
        InputManager::GetInstance().Update();
        stateStack.top()->Update(dt);

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

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

int Game::GetHeight()
{
    return height;
}

int Game::GetWidth()
{
    return width;
}