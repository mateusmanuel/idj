#include "game.h"

int main()
{
    Game::GetInstance().Init("Mateus Manuel Rodrigues Bezerra 14/0063978", 1024, 600);
    Game::GetInstance().Run();
    Game::GetInstance().~Game();

    return 0;
}

