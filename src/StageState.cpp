#include "SDL2/SDL.h"

#include "StageState.h"
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
#include "TitleState.h"
#include "Game.h"

StageState::StageState()
{
    quitRequested = false;
	started = false;

    backgroundMusic = Music("assets/audio/stageState.ogg");
    backgroundMusic.Play(-1);
        
    GameObject* bg = new GameObject();
    bg->AddComponent(new Sprite(*bg, "assets/img/ocean.jpg"));
	bg->AddComponent(new CameraFollower(*bg));
	objectArray.emplace_back(bg);

	GameObject* map = new GameObject();
	TileSet* tile = new TileSet(*map, 64, 64, "assets/img/tileset.png");
	TileMap* tileMap = new TileMap(*map, "assets/map/tileMap.txt", tile);
	map->box.y = map->box.x = 0;
	map->AddComponent(tileMap);
	objectArray.emplace_back(map);

	GameObject* alienGO = new GameObject();
	Alien* alien = new Alien(*alienGO, 6);
	alienGO->box.x = 512;
	alienGO->box.y = 300;
	alienGO->AddComponent(alien);
	objectArray.emplace_back(alienGO);

	alienGO = new GameObject();
	alien = new Alien(*alienGO, 4);
	alienGO->box.x = 996;
	alienGO->box.y = 980;
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

StageState::~StageState()
{
    objectArray.clear();
}

void StageState::LoadAssets()
{

}

void StageState::Start()
{
	LoadAssets();

	StartArray();
}

void StageState::Update(float dt)
{
	Camera::Update(dt);

	if(InputManager::GetInstance().KeyPress(SDLK_ESCAPE) || InputManager::GetInstance().QuitRequested())
	{
		popRequested = true;
		TitleState* titleState = new TitleState();
        Game::GetInstance().Push(titleState);
	}

	UpdateArray(dt);

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

void StageState::Render()
{
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

void StageState::Pause()
{

}

void StageState::Resume()
{

}