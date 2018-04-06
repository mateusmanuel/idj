#include "SDL2/SDL.h"

#include "State.h"
#include "Sprite.h"
#include "Sound.h"
#include "Face.h"

State::State()
{
    quitRequested = false;

    music = new Music("assets/audio/stageState.ogg");
    music->Play(-1);
        
    bg = new GameObject();
    bg->AddComponent(new Sprite(*bg, "assets/img/ocean.jpg"));
}

State::~State()
{
    delete bg;
    delete music;
    objectArray.clear();
}

void State::LoadAssets()
{

}

void State::Update(float dt)
{
    Input();

	for(int i = 0; i < (int) objectArray.size(); ++i)
	{
		objectArray[i]->Update(0.0);
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

	for(int i = 0; i < (int) objectArray.size(); ++i)
	{
		objectArray[i]->Render();
	}
}

bool State::QuitRequested()
{
    return quitRequested;
}

void State::AddObject(int mouseX, int mouseY)
{
	GameObject* enemie = new GameObject();
	Sprite* enemieSprite = new Sprite(*enemie, "assets/img/penguinface.png");
	enemie->AddComponent(enemieSprite);
	enemie->box = Rect(mouseX, mouseY, enemieSprite->GetWidth(), enemieSprite->GetHeight());
	enemie->AddComponent(new Sound(*enemie, "assets/audio/boom.wav"));
	enemie->AddComponent(new Face(*enemie));
    
	objectArray.emplace_back(enemie);
}

// Stuck soon
void State::Input()
{
	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}

		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {
			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				if(go->box.Contains( {(float)mouseX, (float)mouseY} ) ) {
					Face* face = (Face*)go->GetComponent( "Face" );
					if ( nullptr != face ) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
                Vec2* objPos = new Vec2( 200, 0 );
                objPos->Rotate( -M_PI + M_PI*(rand() % 1001)/500.0 );
                *objPos += *(new Vec2( mouseX, mouseY ));
				AddObject((int)objPos->x, (int)objPos->y);
			}
		}
	}
}