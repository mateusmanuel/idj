#include "GameObject.h"

#include <algorithm>

GameObject::GameObject()
{
    isDead = false;
    started = false;
    angleDeg = 0.0;
}

GameObject::~GameObject()
{
    for(auto it: components)
    {
        delete(it);
    }
    components.clear();
}

void GameObject::Start()
{
    for(auto it: components)
    {
        it->Start();
    }
    started = true;
}

void GameObject::Update(float dt)
{
    for(auto it: components)
    {
        it->Update(dt);
    }
}

void GameObject::Render()
{
    for(auto it: components)
    {
        it->Render();
    }
}

bool GameObject::IsDead()
{
    return isDead;
}

void GameObject::RequestDelete()
{
    isDead = true;
}

void GameObject::AddComponent(Component* cpt)
{
    components.push_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt)
{
    components.erase(std::remove(components.begin(), components.end(), cpt), components.end());
}

Component* GameObject::GetComponent(std::string type)
{
    auto it = find_if(components.begin(), components.end(), [&type](Component* cpt) {return cpt->Is(type);});
    
    if (it == components.end())
        return nullptr;

    return *it;    
}

void GameObject::NotifyCollision(GameObject& other)
{
	for (auto cpt : components)
    {
		cpt->NotifyCollision(other);
	}
}