#include "InputManager.h"

InputManager& InputManager::GetInstance()
{
    static InputManager inputManager;
    return inputManager;
}

InputManager::InputManager()
{
    mouseState[6] = {false};
    mouseUpdate[6] = {0};
    quitRequested = false;
    updateCounter = 0;
    mouseX = mouseY = 0;
}

void InputManager::Update()
{
    SDL_Event event;

	SDL_GetMouseState(&mouseX, &mouseY);
    quitRequested = false;
    updateCounter++;

	while (SDL_PollEvent(&event)) {

        switch(event.type)
        {
            case SDL_QUIT:
                quitRequested = true;
                break;

            case SDL_MOUSEBUTTONDOWN:
                mouseState[event.button.button] = true;
                mouseUpdate[event.button.button] = updateCounter;
                break;

            case SDL_MOUSEBUTTONUP:
                mouseState[event.button.button] = false;
                mouseUpdate[event.button.button] = updateCounter;
                break;
            
            case SDL_KEYDOWN:
                if(event.key.repeat)
                    continue;
                printf("%d\n", event.key.keysym.sym);
                keyState[event.key.keysym.sym] = true;
                keyUpdate[event.key.keysym.sym] = updateCounter;
                break;

            case SDL_KEYUP:             
                keyState[event.key.keysym.sym] = false;
                keyUpdate[event.key.keysym.sym] = updateCounter;   
                break;

            default:
                break;
        }
	}
}

bool InputManager::KeyPress(int key)
{
    auto it = keyUpdate.find(key);
    if(it != keyUpdate.end())
    {
        if(it->second == updateCounter)
        {
            return keyState[key];
        }
    }    
    return false;
}

bool InputManager::KeyRelease(int key)
{
    auto it = keyUpdate.find(key);
    if(it != keyUpdate.end())
    {
        if(it->second == updateCounter)
        {
            return !keyState[key];
        }
    }
    return false;
}

bool InputManager::IsKeyDown(int key)
{
    auto it = keyState.find(key);
    if(it != keyState.end())
    {
        return keyState[key];
    }
    return false;
}

bool InputManager::MousePress(int button)
{
    if(mouseUpdate[button] == updateCounter)
    {
        return mouseState[button];
    }
    return false;
}

bool InputManager::MouseRelease(int button)
{
    if(mouseUpdate[button] == updateCounter)
    {
        return !mouseState[button];
    }
    return false;
}

bool InputManager::IsMouseDown(int button)
{
    return mouseState[button];
}

int InputManager::GetMouseX()
{
    return mouseX;
}

int InputManager::GetMouseY()
{
    return mouseY;
}

bool InputManager::QuitRequested()
{
    return quitRequested;
}

InputManager::~InputManager()
{

}