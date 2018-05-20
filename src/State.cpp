#include "State.h"

State::State()
{
    quitRequested = false;
    popRequested = false;
    started = false;
}

State::~State()
{
    objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go)
{
	std::shared_ptr<GameObject> goPtr(go);

	objectArray.push_back(goPtr);
	
	if(started)
	{
		go->Start();
	}

	return std::weak_ptr<GameObject> (goPtr);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go)
{
	for(int i = 0; i < (int) objectArray.size(); ++i)
	{
		if(objectArray[i].get() == go)
		{
			return std::weak_ptr<GameObject> (std::shared_ptr<GameObject> (objectArray[i]));
		}
	}
	return std::weak_ptr<GameObject> ();
}

bool State::PopRequested()
{
    return popRequested;
}

bool State::QuitRequested()
{
    return quitRequested;
}

void State::StartArray()
{
    for(int i = 0; i < (int) objectArray.size(); ++i)
	{
		objectArray[i].get()->Start();
	}

    started = true;
}

void State::UpdateArray(float dt)
{
    for(int i = 0; i < (int) objectArray.size(); ++i)
	{
		objectArray[i].get()->Update(dt);
	}
}

void State::RenderArray()
{
    for(int i = 0; i < (int) objectArray.size(); ++i)
	{
		objectArray[i].get()->Render();
	}
}
