#include "Game.h"

void Game::Initial(Player &PlayerOne,Player &PlayerTwo)
{
    background.Initial();
    weapon1.Initial(DEFAULT,true);//weapon type
    PlayerOne.Initial(0, 550, 0, 1);//x,y,direction
    weapon2.Initial(DEFAULT,false);//weapon type
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

        background.Run(weapon1,weapon2);

        weapon1.Run(key, PlayerOne);
        PlayerOne.Run(key);
        weapon2.Run(key, PlayerTwo);
        PlayerTwo.Run(key);
        obstacle1.Run(weapon1,PlayerOne,weapon2,PlayerTwo);
        obstacle2.Run(weapon1,PlayerOne,weapon2,PlayerTwo);
        if (PlayerOne.health<=0)
        {
            terminate=1;
        }
        if (PlayerTwo.health<=0)
        {
            terminate=1;
        }
        FsSwapBuffers();
        FsSleep(10);
    }
    status=1;
}


void checkCollision(Player &player1, Player &player2, Weapon weapon1, Weapon weapon2)
{
    int w = 10;
    int h = 10;
    if (player1.getStatus() == 1) {
        if ((weapon1.GetBullet()->x() > player1.getX()-w)
            && (weapon1.GetBullet()->x() < player1.getY()+w)
            && (weapon1.GetBullet()->y() > player1.getX()-h)
            && (weapon1.GetBullet()->y() < player1.getY()+h))
        {
            player1.hit = 1;
        }
    }
    else {
        if ((weapon1.GetBullet()->x() > player2.getX()-w)
            && (weapon1.GetBullet()->x() < player2.getY()+w)
            && (weapon1.GetBullet()->y() > player2.getX()-h)
            && (weapon1.GetBullet()->y() < player2.getY()+h))
        {
            player2.hit = 1;
        }
    }
}


