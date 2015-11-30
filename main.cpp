#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "fssimplewindow.h"
#include "yspng.h"
#include <ctype.h>
#include <iostream>
#include <fstream>
#include "ysglfontdata.h"
#include <vector>




#include "Intro.hpp"
#include "Flash.hpp"
#include "Shop.hpp"
#include "Game.h"

/***
 
 author: santok@andrew.cmu.edu
 
 **/
int  DrawButton(int lb, double mxl,double myl, double mxh, double myh,double textx, double texty, char str[])
{
    int lb1,mb,rb,mxm,mym;
    FsGetMouseEvent(lb1,mb,rb,mxm,mym);
    if((mxm<=mxh)&&(mxm>=mxl)&&(mym>=myl)&&(mym<=myh)&&(lb==1))
    {
        return 1;
    }
    return 0;
}


void MenuBackGround()
{
    YsRawPngDecoder decoder;
    decoder.Decode("MenubBackgorund.png");
    decoder.Flip();
    glRasterPos2d(0,decoder.hei-1);
    glDrawPixels(decoder.wid,decoder.hei,GL_RGBA,GL_UNSIGNED_BYTE,decoder.rgba);
}



int main()
{
    //Initailize two player
    Player PlayerOne;
    Player PlayerTwo;

    // Open window
    FsOpenWindow(0, 0, 800, 600, 1);
    
    //Get into Intro page and fetch username
    TextString UserName1, UserName2;
    Intro(&UserName1, &UserName2);
    
    //Change user name to str, ready to pass into player class
    const char *user1namestr=UserName1.GetPointer();
    const char *user2namestr=UserName2.GetPointer();
    
    //pass user name into read properties
    //PlayerOne.ReadProperties();
    //PlayerOne.ReadProperties();
    
    //do button's string
    char Shopstring[20]="Shop";
    char gamestring[]="Start a game";
    char flashstring[]="enter flash";
    
    //Initialize some variable for gmae status
    int status =1;
    int switchplayer=1;
    int gamebuttonstat=0;
    int flashbuttonplayer1stat=0;
    int flashbuttonplayer2stat=0;
    int shopbuttonplayer1stat=0;
    int shopbuttonplayer2stat=0;
    
    
    
    // enter while loop, depending on "status"
    while(FSKEY_ESC!=FsInkey())
    {
        //FsPollDevice();
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        

        
        if (status==1)//menu
        {
            MenuBackGround();
            FsPollDevice();
            int lbmain,mb,rb,mxm,mym;
            FsGetMouseEvent(lbmain,mb,rb,mxm,mym);
            
            flashbuttonplayer1stat=DrawButton(lbmain, 63, 362, 251, 507, 0, 150,flashstring);
            flashbuttonplayer2stat=DrawButton(lbmain, 563, 359, 755, 504, 0, 150, flashstring);
            shopbuttonplayer1stat=DrawButton(lbmain, 30, 98, 222, 249, 0, 350,Shopstring);
            shopbuttonplayer2stat=DrawButton(lbmain, 575, 96, 765, 220, 700, 350, Shopstring);
            gamebuttonstat=DrawButton(lbmain, 300, 250,500,350,320,300,gamestring);
            if (shopbuttonplayer1stat==1)
            {
                status=2;
                switchplayer=1;
                
            }
            if (shopbuttonplayer2stat==1)
            {
                status=2;
                switchplayer=2;
                
            }

            if (flashbuttonplayer1stat==1)
            {
                status=3;
                switchplayer=1;
                
            }
            if (flashbuttonplayer2stat==1)
            {
                status=3;
                switchplayer=2;
                
            }
            if (gamebuttonstat==1)
            {
                status=4;
            }
            
            
            
        }
        
            
            
         
        if (status==2)//shop
        {
            Player player1;
            player1.setMoney(100);
            Shop shop;
            shop.AssignWeaponCheck(player1); // Assign weapon list from player to shop
            shop.Run(player1, status); // should input money
        }
        if (status==3)//flashcard
        {
            Flash test;
            test.Set(5, 10);
            test.Display(status);
        }
        if (status==4)//run
        {
            Game game;
            game.Initial();
            game.Run(status);
        }
        
        FsSwapBuffers();
        FsSleep(10);

    }
    

    
}
