#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "fssimplewindow.h"
#include "yspng.h"
#include <ctype.h>
#include <iostream>
#include <fstream>
#include "ysglfontdata.h"
#include <stdio.h>
#include <math.h>
#include <vector>

/**********************************  above function header****/
/**********************************  following page header****/



#include "Intro.hpp"
#include "Flash.hpp"
#include "player.h"
#include "character.h"
#include "Shop.hpp"
/***
 
 author: santok@andrew.cmu.edu
 
 **/
int  DrawButton(int onoff, double mxl,double myl, double mxh, double myh,double textx, double texty, char str[])
{
    int lb,mb,rb,mxm,mym;
    FsGetMouseEvent(lb,mb,rb,mxm,mym);
    double dark=onoff*0.2;
    glColor3d(1, 0.5+dark, 0.5+dark);
    glBegin(GL_QUADS);
    glVertex2d(mxl, myl);
    glVertex2d(mxl, myh);
    glVertex2d(mxh, myh);
    glVertex2d(mxh, myl);
    glEnd();
    
    glColor3d(1,1,1);
    glRasterPos2d(textx,texty);
    YsGlDrawFontBitmap12x16(str);
    
    if((mxm<=mxh)&&(mxm>=mxl)&&(mym>=myl)&&(mym<=myh)&&(lb==1))
    {
        return 1;
    }
    return 0;
}


class Circle
{
protected:
    double position[2];
    double rad;
    double color[3];
    const double YS_PI=3.1415927;
    int state;// on , off , dark
public:
    void GetPro(double pos[],double col[],double radian,int curstate)
    {
        position[0]=pos[0];
        position[1]=pos[1];
        color[0]=col[0];
        color[1]=col[1];
        color[2]=col[2];
        rad=radian;
        state=curstate;
    }

    void DrawCircle()
    {
        glBegin(GL_POLYGON);
        double i;
        
        for (i=0;i<64;i++)
        {
            double anglea=(double)i*YS_PI/32.0;
            double xy[2]={position[0]+cos(anglea)*(double)rad,position[1]+sin(anglea)*(double)rad};
            glColor3d(color[0], color[1],color[2]);
            glVertex2d(xy[0],xy[1]);
        }
        glEnd();
    }
};
class Text
{
protected:
    double position[2];
    char str[20];
    double color[3];
    const double YS_PI=3.1415927;
    int state;// on , off , dark
public:
    void GetPro(double pos[],double col[],char string[],int curstate)
    {
        position[0]=pos[0];
        position[1]=pos[1];
        color[0]=col[0];
        color[1]=col[1];
        color[2]=col[2];
        strcpy(str, string);
        state=curstate;
    }
    
    void DrawText()
    {
        glColor3d(color[0],color[1],color[2]);
        glRasterPos2d(position[0],position[1]);
        YsGlDrawFontBitmap10x14(str);
    }
};

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
    Player one;
    Player two;

    /**
        IntroPage intropage;
    Menu menu;
    Shop shop;
    Flash flash;
    Game game;
     **/
    
    FsOpenWindow(0, 0, 800, 600, 1);

    TextString UserName1, UserName2;
    Intro(&UserName1, &UserName2);
    
    
    UserName1.Print();
    
    Circle circle;
    Text text;
    
    double pos[2]={60,60};
    double col[3]={0,0,256};
    double rad=50;
    int state=1;
    circle.GetPro(pos,col,rad,state);
    
    
    double postext[2]={200,300};
    double coltext[3]={0,1,256};
    char texttext[20]="Player1";
    char Shopstring[20]="Shop";
    char gamestring[]="Start a game";
    char flashstring[]="enter flash";

    int statetext=1;
    text.GetPro(postext, coltext, texttext, statetext);
    
    int status =1;
    int switchplayer=1;
    int gamebuttonstat=0;
    int flashbuttonplayer1stat=0;
    int flashbuttonplayer2stat=0;
    int shopbuttonplayer1stat=0;
    int shopbuttonplayer2stat=0;
    int money = 100;
    while(FSKEY_ESC!=FsInkey())
    {
        FsPollDevice();
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        

        switch (status)
        {
            case 1://menu
                MenuBackGround();
                //circle.DrawCircle();
                //text.DrawText();
                
                flashbuttonplayer1stat=DrawButton(1, 0, 100, 100, 200, 0, 150,flashstring);
                flashbuttonplayer2stat=DrawButton(1, 700, 100, 800, 200, 700, 150, flashstring);
                shopbuttonplayer1stat=DrawButton(1, 0, 300, 100, 400, 0, 350,Shopstring);
                shopbuttonplayer2stat=DrawButton(1, 700, 300, 800, 400, 700, 350, Shopstring);
                gamebuttonstat=DrawButton(1, 300, 250,500,350,320,300,gamestring);
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
                if (flashbuttonplayer1stat==1)
                {
                    status=3;
                    switchplayer=2;
                    
                }
                break;
                
                
                
             
            case 2://shop
                Player player1;
                player1.setMoney(100);
                Shop shop;
                shop.AssignWeaponCheck(player1); // Assign weapon list from player to shop
            
                shop.Run(player1, status); // should input money
                status=1;
                break;

              
            
            case 3://flashcard
                Flash test;
                test.Set(5, 10);
                test.Display(status);
                
                break;
             
                
                /**
            case 4://game
                //Game.game();
            case 5://
              **/
        }

        
        
        

        
        FsSwapBuffers();
        FsSleep(10);

    }
    

    
}
