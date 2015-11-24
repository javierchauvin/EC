#include "Game.h"

void Game::Initial(void)
{
    background.Initial();
    weapon.Initial(DEFAULT);//weapon type
    player.Initial();//x,y,direction
    obstacle1.Initial(200, 30, 150, 1, 1);//x,y,size,direction,speed
    obstacle2.Initial(100, 150, 100, 0, 2);//x,y,size,direction,speed
}
void Game::Run(int &status)
{
    auto key=FsInkey();
    while (key!=FSKEY_ESC)
    {
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    background.Run(weapon);
    weapon.Run(key);
    player.Run();
    obstacle1.Run(weapon,player);
    obstacle2.Run(weapon,player);
    if (key==FSKEY_ESC)
    {
        status=1;
    }
    FsSwapBuffers();
    FsSleep(10);
    }
    status=1;
}

