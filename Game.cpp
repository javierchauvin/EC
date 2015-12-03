#include "Game.h"

void Game::Initial(Player &PlayerOne,Player &PlayerTwo)
{
    background.Initial();
    weapon1.Initial(NINE_MM,true);//weapon type
    PlayerOne.Initial(50, 550, 0, 1);//x,y,direction
    weapon2.Initial(CANNON,false);//weapon type
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

        PlayerOne.setStatus(weapon1.GetWeaponState());
        PlayerTwo.setStatus(weapon2.GetWeaponState());

        
        background.Run(weapon1,weapon2);

		if (weapon1.GetWeaponState() && weapon1.GetBullet()->GetState()){
			weapon1.SetState( false );
			weapon2.SetState( true );
		}
		if (weapon2.GetWeaponState() && weapon2.GetBullet()->GetState()){
			weapon1.SetState( true );
			weapon2.SetState( false );
		}

        weapon1.Run(key, PlayerOne);
        PlayerOne.Run(key);
        weapon2.Run(key, PlayerTwo);
        PlayerTwo.Run(key);
        obstacle1.Run(weapon1,PlayerOne,weapon2,PlayerTwo);
        obstacle2.Run(weapon1,PlayerOne,weapon2,PlayerTwo);
        if (PlayerOne.health<=0)
        {
            terminate=1;
            PlayerOne.health=100;
            PlayerTwo.health=100;
            Initial(PlayerOne, PlayerTwo);

            
        }
        if (PlayerTwo.health<=0)
        {
            terminate=1;
            PlayerOne.health=100;
            PlayerTwo.health=100;
            Initial(PlayerOne, PlayerTwo);
        }
        
        //check bullet collision with player
        checkCollision(PlayerOne, PlayerTwo, weapon1, weapon2);

        FsSwapBuffers();
        FsSleep(10);
    }
    status=1;
}



void checkCollision(Player &player1, Player &player2, Weapon &weapon1, Weapon &weapon2)
{
    int w = 100;
    int h = 100;
    if (player1.getStatus() == 1) {
        if ((weapon1.GetBullet()->x() > player2.getX()-w)
            && (weapon1.GetBullet()->x() < player2.getX()+w)
            && (weapon1.GetBullet()->y() > player2.getY()-h)
            && (weapon1.GetBullet()->y() < player2.getY()+h)
            && (weapon1.GetBullet()->x() < 400))
        {
            player2.hit = 1;
            weapon1.GetBullet()->SetState(false);
        }
    }
    /* player 2 */
    else if (player2.getStatus() == 1) {
        if ((weapon2.GetBullet()->x() > player1.getX()-w)
            && (weapon2.GetBullet()->x() < player1.getX()+w)
            && (weapon2.GetBullet()->y() > player1.getY()-h)
            && (weapon2.GetBullet()->y() < player1.getY()+h)
            && (weapon2.GetBullet()->x() > 400))
        {
            player1.hit = 1;
            weapon2.GetBullet()->SetState(false);
        }
    }
}


