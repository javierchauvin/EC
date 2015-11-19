#include "Game.h"

void Game::Initial(void)
{
    bacground.Initial();
    obstacle.Initial();
    weapon.Initial();
    bullet.Initial();
    player.Initial();
    character.Initial();
}
void Game::Run(void)
{
    bacground.Run();
    obstacle.Run();
    weapon.Run();
    bullet.Run();
    player.Run();
    character.Run();
}

