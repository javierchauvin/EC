#include "Game.h"

void Game::Initial(void)
{
    bacground.Initial();
    obstacle1.Initial(200, 30, 150, 1, 1);//x,y,size,direction,speed
    obstacle2.Initial(100, 150, 100, 0, 2);
    weapon.Initial();
    bullet.Initial();
    player.Initial();
    character.Initial();
}
void Game::Run(void)
{
    FsPollDevice();
    auto key=FsInkey();
    bacground.Run();
    obstacle1.Run(const Bullet &bullet,const Player &player);
    obstacle2.Run(const Bullet &bullet,const Player &player);
    bullet.Run();
    player.Run();
    character.Run();
}

