#include "Game.h"

void Game::Initial(void)
{
    background.Initial();
    weapon.Initial(DEFAULT);//weapon type
    player.Initial(100, 500, 1);//x,y,direction
    obstacle1.Initial(200, 30, 150, 1, 1);//x,y,size,direction,speed
    obstacle2.Initial(100, 150, 100, 0, 2);//x,y,size,direction,speed
}
void Game::Run(void)
{
    auto key=FsInkey();
    background.Run(weapon);
    weapon.Run(key,player);
    player.Run();
    obstacle1.Run(weapon,player);
    obstacle2.Run(weapon,player);
}

