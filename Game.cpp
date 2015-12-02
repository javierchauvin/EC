#include "Game.h"

void Game::Initial(Player &PlayerOne,Player &PlayerTwo)
{
    background.Initial();
    weapon1.Initial(DEFAULT);//weapon type
    PlayerOne.Initial(0, 550, 0, 1);//x,y,direction
    weapon2.Initial(DEFAULT);//weapon type
    PlayerTwo.Initial(700, 550, 1, 0);//x,y,direction
    obstacle1.Initial(200, 30, 150, 1, 1);//x,y,size,direction,speed
    obstacle2.Initial(100, 150, 100, 0, 2);//x,y,size,direction,speed
}
void Game::Run(int &status,Player &PlayerOne,Player &PlayerTwo)
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
        weapon1.Run(key, PlayerOne);
        PlayerOne.Run(key);
        weapon2.Run(key, PlayerTwo);
        PlayerTwo.Run(key);
        obstacle1.Run(weapon1,PlayerOne,weapon2,PlayerTwo);
        obstacle2.Run(weapon1,PlayerOne,weapon2,PlayerTwo);

        FsSwapBuffers();
        FsSleep(10);
    }
    status=1;
}





