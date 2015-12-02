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
    
    //Initialize shop & flash
    Shop shop;

    // Open window
    FsOpenWindow(0, 0, 800, 600, 1);
    
    //Get into Intro page and fetch username
    TextString UserName1, UserName2;
    Intro(&UserName1, &UserName2);
    
    //Change user name to str, ready to pass into player class
    const char *user1namestr=UserName1.GetPointer();
    const char *user2namestr=UserName2.GetPointer();
    
    //pass user name into read properties
    PlayerOne.ReadProperties(user1namestr);
    PlayerTwo.ReadProperties(user2namestr);
    
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
    int GameCharge = 0;
    
    Game game;
    game.Initial();
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
            if (switchplayer == 1){
                shop.AssignWeaponCheck(PlayerOne); // Assign weapon list to shop
                shop.Run(PlayerOne, status); // should input money
            }
            else if (switchplayer == 2){
                shop.AssignWeaponCheck(PlayerTwo); // Assign weapon list to shop
                shop.Run(PlayerTwo, status); // should input money
            }
            
        }
        if (status==3)//flashcard
        {
            Flash flash;
            if (switchplayer == 1){
                flash.Set(PlayerOne.getMoney(), GameCharge);
                flash.Display(status);
                PlayerOne.setMoney(flash.ReturnMoney());
                GameCharge =flash.ReturnGameCharge();
            }
            else if (switchplayer == 2){
                flash.Set(PlayerTwo.getMoney(), GameCharge);
                flash.Display(status);
                PlayerTwo.setMoney(flash.ReturnMoney());
                GameCharge =flash.ReturnGameCharge();
            }
        }
        if (status==4)//run
        {
            
            game.Run(status);
        }
        
        FsSwapBuffers();
        FsSleep(10);

    }
    
    
    
    
    PlayerOne.SaveProperties();
    PlayerTwo.SaveProperties();
}
