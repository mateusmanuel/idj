#include "SDL2/SDL.h"

#include "State.h"
#include "Sprite.h"
#include "Sound.h"
#include "Face.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "PenguinBody.h"
#include "Collider.h"
#include "Collision.h"

State::State()
{
    quitRequested = false;
	started = false;

    music = new Music("assets/audio/stageState.ogg");
    music->Play(-1);
        
    bg = new GameObject();
    bg->AddComponent(new Sprite(*bg, "assets/img/ocean.jpg"));
	bg->AddComponent(new CameraFollower(*bg));

	map = new GameObject();
	TileSet* tile = new TileSet(*map, 64, 64, "assets/img/tileset.png");
	TileMap* tileMap = new TileMap(*map, "assets/map/tileMap.txt", tile);
	map->box.y = map->box.x = 0;
	map->AddComponent(tileMap);

	GameObject* alienGO = new GameObject();
	Alien* alien = new Alien(*alienGO, 6);
	alienGO->box.x = 512;
	alienGO->box.y = 300;
	alienGO->AddComponent(alien);
	objectArray.emplace_back(alienGO);

	GameObject* penguins = new GameObject();
    PenguinBody* penguinBody = new PenguinBody(*penguins);
	penguinBody->player = penguinBody;
	penguins->box.x = 704;
	penguins->box.y = 640;
	
	penguins->AddComponent(penguinBody);
	objectArray.emplace_back(penguins);

	//Camera::pos.x = Camera::pos.y = 0;
	Camera::Follow(penguins);
}

State::~State()
{
    delete bg;
	delete map;
    delete music;
    objectArray.clear();
}

void State::LoadAssets()
{

}

void State::Start()
{
	LoadAssets();

	bg->Start();
	map->Start();

	for(int i = 0; i < (int) objectArray.size(); ++i)
	{
		objectArray[i]->Start();
	}

	started = true;	
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

void State::Update(float dt)
{
	Camera::Update(dt);

	bg->Update(dt);
	map->Update(dt);

	if(InputManager::GetInstance().KeyPress(SDLK_ESCAPE) || InputManager::GetInstance().QuitRequested())
	{
		quitRequested = true;
	}

	if(InputManager::GetInstance().KeyPress(SDLK_SPACE))
	{
		Vec2* objPos = new Vec2(200, 0);
        objPos->Rotate(-M_PI + M_PI*(rand() % 1001)/500.0);
        *objPos += *(new Vec2(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseX()));
		AddObject((int)objPos->x, (int)objPos->y);
	}

	for(int i = 0; i < (int) objectArray.size(); ++i)
	{
		objectArray[i]->Update(dt);
	}

	for(int i = 0; i < (int) objectArray.size(); ++i) 
	{
		Collider* a = (Collider*)objectArray[i]->GetComponent("Collider");
		if (a != nullptr) 
		{
			for(int j = i+1; j < (int) objectArray.size(); ++j) 
			{
				Collider* b = (Collider*)objectArray[j]->GetComponent("Collider");
				if (b != nullptr) 
				{
					if (Collision::IsColliding(a->box, b->box, objectArray[i]->angleDeg * (M_PI / 180), objectArray[j]->angleDeg * M_PI / 180)) 
					{
						objectArray[i]->NotifyCollision(*objectArray[j].get());
						objectArray[j]->NotifyCollision(*objectArray[i].get());
					}
				}
			}
		}
	}


	for(int i = 0; i < (int) objectArray.size(); ++i)
	{
		if(objectArray[i]->IsDead())
		{
			objectArray.erase(objectArray.begin() + i);
		}
	}
}

void State::Render()
{
 	bg->Render();
	map->Render();

	for(int i = 0; i < (int) objectArray.size(); ++i)
	{
		if(objectArray[i]->GetComponent("TileMap") != nullptr)
		{
			objectArray[i]->box.x = Camera::pos.x;
			objectArray[i]->box.y = Camera::pos.y;
		}
		objectArray[i]->Render();
	}
}

bool State::QuitRequested()
{
    return quitRequested;
}

void State::AddObject(int mouseX, int mouseY)
{
	GameObject* enemy = new GameObject();
	Sprite* enemySprite = new Sprite(*enemy, "assets/img/penguinface.png");
	enemy->AddComponent(enemySprite);
	enemy->AddComponent(new Sound(*enemy, "assets/audio/boom.wav"));
	enemy->AddComponent(new Face(*enemy));
	enemy->box = Rect(mouseX, mouseY, enemySprite->GetWidth(), enemySprite->GetHeight());
    
	objectArray.emplace_back(enemy);
}
