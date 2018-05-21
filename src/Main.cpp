#include "Game.h"
#include "TitleState.h"

int main()
{
    Game::GetInstance().Init("Mateus Manuel Rodrigues Bezerra 14/0063978", 1024, 600);
    Game::GetInstance().Push(new TitleState());
    Game::GetInstance().Run();
    Game::GetInstance().~Game();

    return 0;
}

