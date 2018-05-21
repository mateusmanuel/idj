#include "Alien.h"

#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "Game.h"
#include "Minion.h"
#include "Collider.h"
#include "Bullet.h"
#include "Sound.h"
#include "PenguinBody.h"
#include "GameData.h"
#include "EndState.h"

#define EPS 1
#define SPEED 5
#define COOLDOWN 2

int Alien::alienCount = 0;

Alien::Alien(GameObject& associated, int nMinions) : Component(associated)
{
    state = RESTING;

    associated.AddComponent(new Collider(associated));

    Sprite* alienSprite = new Sprite(associated, "assets/img/alien.png");
    associated.AddComponent(alienSprite);
    
    associated.box.h = alienSprite->GetHeight();
    associated.box.w = alienSprite->GetHeight();

    minionArray.resize(nMinions);

    speed = Vec2(100, 100);
    hp = 30;
    restTimer = Timer();
    alienCount++;
}

void Alien::Start()
{  
    State &state = Game::GetInstance().GetCurrentState();

    std::weak_ptr<GameObject> alienWeakPtr(state.GetObjectPtr(&associated));
    for(int i = 0; i < (int) minionArray.size(); ++i)
    {
        GameObject* minionGO = new GameObject();
        Minion* minion = new Minion(*minionGO, alienWeakPtr, i * 360.0/minionArray.size());
        minionGO->AddComponent(minion);
        minionArray[i] = state.AddObject(minionGO);
    }
}

Alien::~Alien()
{
    minionArray.clear();
}

void Alien::Update(float dt)
{
    if(PenguinBody::player != nullptr)
    {
        if(state == RESTING)
        {
			restTimer.Update(dt);
		
        	if (restTimer.Get() > COOLDOWN)
            {
				destination = PenguinBody::player->Center();
				state = MOVING;

                float angle = atan2(destination.y - associated.box.Center().y, destination.x - associated.box.Center().x);
                this->speed.x = SPEED * cos(angle);
                this->speed.y = SPEED * sin(angle);
			}
		}
        else if(state == MOVING)
        {
            if(destination.Distance(associated.box.Center()) > speed.Length() * dt)
            {
                associated.box.x += speed.x * dt;
                associated.box.y += speed.y * dt;
            }
            else
            {
                associated.box.x = destination.x - associated.box.w/2;
				associated.box.y = destination.y - associated.box.h/2;

                Vec2 target = PenguinBody::player->Center();
                Minion* minion = GetClosestMinion(target);
                minion->Shoot(target);

                state = RESTING;
				restTimer.Restart();
            }
        }
    }

    if(hp <= 0)
    {
        GameObject* alienDeath = new GameObject();
		alienDeath->box.x = associated.box.x;
		alienDeath->box.y = associated.box.y;

		alienDeath->AddComponent(new Sprite(*alienDeath, "assets/img/aliendeath.png", 4, 0.5, 2));
		Sound* sound = new Sound(*alienDeath, "assets/audio/boom.wav");
        sound->Play();
        alienDeath->AddComponent(sound);

        Game::GetInstance().GetCurrentState().AddObject(alienDeath);
        associated.RequestDelete();

        Alien::alienCount--;

        if(Alien::alienCount == 0)
        {
            Camera::pos = Vec2(0,0);
            GameData::playerVictory = true;
            EndState *endState = new EndState();
            Game::GetInstance().Push(endState);
        }
    }
}

void Alien::Render()
{
    associated.angleDeg -= 0.25;
}

bool Alien::Is(std::string type)
{
    return type == "Alien";
}

Minion* Alien::GetClosestMinion(Vec2 pos)
{

    double minDist = 1e6;
    GameObject* minionGOClose;

    for(int i = 0; i < (int) minionArray.size(); i++){
        GameObject* minionGo = minionArray[i].lock().get();
        
        double dist = minionGo->box.Center().Distance(pos);
        
        if(dist < minDist){
            minionGOClose = minionGo;
            minDist = dist;
        }
    }

    return (Minion*)minionGOClose->GetComponent("Minion");
}

void Alien::NotifyCollision(GameObject& other)
{
	Bullet* bullet = (Bullet*)other.GetComponent("Bullet");
	if(bullet != nullptr)
    {
		if(not bullet->targetsPlayer)
        {
			hp -= bullet->GetDamage();
		}
	}
}