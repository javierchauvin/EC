#include "Game.h"

void Game::Initial(void)
{
    background.Initial();
    weapon1.Initial(DEFAULT);//weapon type
    player1.Initial();//x,y,direction
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
    background.Run(weapon1);
    weapon1.Run(key, player1.getX()+80 , player1.getY()-37);
    player1.Run();
    weapon2.Run(key, player2.getX()+80 , player2.getY()-37);
    player2.Run();
    obstacle1.Run(weapon1,player1,weapon2,player2);
    obstacle2.Run(weapon1,player1,weapon2,player2);
    FsSwapBuffers();
    FsSleep(10);
    }
    status=1;
}

