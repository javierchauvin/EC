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
    int terminate=0;
    while (terminate!=1)
    {
    FsPollDevice();
    auto key=FsInkey();
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    if (key==FSKEY_ESC)
    {
        terminate=1;
    }
    background.Run(weapon);
    weapon.Run(key,0,0);
    player.Run();
    obstacle1.Run(weapon,player);
    obstacle2.Run(weapon,player);
    FsSwapBuffers();
    FsSleep(10);
    }
    status=1;
}

