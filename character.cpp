//
//  character.cpp
//  FINAL PROJECT
//
//  Created by Kelly Cheng on 11/16/15.
//  Copyright © 2015 Kelly Cheng. All rights reserved.
//

#include <math.h>
#include "Game.h"
#include "fssimplewindow.h"

#define YsPi 3.1415927

Character::Character(){}
Character::~Character(){}

Tank::Tank(){}
Tank::~Tank(){}
void Tank::drawCharacter(int x, int y, int direction){
    
//the tank is actually a minion now
    
    double xx=(double)(x);
    double yy=(double)(y-55);
    double r=30;
    
    glColor3d(1.0,0.95,0.0);
    glBegin(GL_TRIANGLE_FAN);
    for(int a=0; a<64; ++a)
    {
        const double radian=YsPi*2.0*(double)a/64.0;
        const double c=cos(radian);
        const double s=sin(radian);
        
        //glVertex2d(xx+c*r,yy+s*r);
        glVertex2d(xx+c*r,yy+s*r);
    }
    glEnd();
    
    xx=(double)(x);
    yy=(double)(y+20);
    r=30;
    glColor3d(0.0,0.0,1.0);
    glBegin(GL_TRIANGLE_FAN);
    for(int a=0; a<64; ++a)
    {
        const double radian=YsPi*2.0*(double)a/64.0;
        const double c=cos(radian);
        const double s=sin(radian);
        
        //glVertex2d(xx+c*r,yy+s*r);
        glVertex2d(xx+c*r,yy+s*r);
    }
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3d(1.0,0.95,0.0);
    //torso
    glVertex2i(x-30,y-55);
    glVertex2i(x-30,y-5);
    glVertex2i(x+30,y-5);
    glVertex2i(x+30,y-55);
    
    glVertex2i(x-30,y-15);
    glVertex2i(x-30,y+25);
    glVertex2i(x+30,y+25);
    glVertex2i(x+30,y-15);
    
    glColor3d(0.0,0.0,1.0);
    //torso
    glVertex2i(x-20,y-15);
    glVertex2i(x-20,y+25);
    glVertex2i(x+20,y+25);
    glVertex2i(x+20,y-15);
    glEnd();
    
    //eyes
    xx=(double)(x-12);
    yy=(double)(y-55);
    r=13;
    
    glColor3d(0.1,0.1,0.1);
    glBegin(GL_TRIANGLE_FAN);
    for(int a=0; a<64; ++a)
    {
        const double radian=YsPi*2.0*(double)a/64.0;
        const double c=cos(radian);
        const double s=sin(radian);
        
        //glVertex2d(xx+c*r,yy+s*r);
        glVertex2d(xx+c*r,yy+s*r);
    }
    glEnd();
    
    r=10;
    glColor3d(1.0,0.95,1.0);
    glBegin(GL_TRIANGLE_FAN);
    for(int a=0; a<64; ++a)
    {
        const double radian=YsPi*2.0*(double)a/64.0;
        const double c=cos(radian);
        const double s=sin(radian);
        
        //glVertex2d(xx+c*r,yy+s*r);
        glVertex2d(xx+c*r,yy+s*r);
    }
    glEnd();
    
    r=4;
    glColor3d(0.0,0.0,0.0);
    glBegin(GL_TRIANGLE_FAN);
    for(int a=0; a<64; ++a)
    {
        const double radian=YsPi*2.0*(double)a/64.0;
        const double c=cos(radian);
        const double s=sin(radian);
        
        //glVertex2d(xx+c*r,yy+s*r);
        glVertex2d(xx+c*r,yy+s*r);
    }
    glEnd();
    
    xx=(double)(x+12);
    yy=(double)(y-55);
    r=13;
    
    glColor3d(0.1,0.1,0.1);
    glBegin(GL_TRIANGLE_FAN);
    for(int a=0; a<64; ++a)
    {
        const double radian=YsPi*2.0*(double)a/64.0;
        const double c=cos(radian);
        const double s=sin(radian);
        
        //glVertex2d(xx+c*r,yy+s*r);
        glVertex2d(xx+c*r,yy+s*r);
    }
    glEnd();
    
    r=10;
    
    glColor3d(1.0,0.95,1.0);
    glBegin(GL_TRIANGLE_FAN);
    for(int a=0; a<64; ++a)
    {
        const double radian=YsPi*2.0*(double)a/64.0;
        const double c=cos(radian);
        const double s=sin(radian);
        
        //glVertex2d(xx+c*r,yy+s*r);
        glVertex2d(xx+c*r,yy+s*r);
    }
    glEnd();
    
    r=4;
    glColor3d(0.0,0.0,0.0);
    glBegin(GL_TRIANGLE_FAN);
    for(int a=0; a<64; ++a)
    {
        const double radian=YsPi*2.0*(double)a/64.0;
        const double c=cos(radian);
        const double s=sin(radian);
        
        //glVertex2d(xx+c*r,yy+s*r);
        glVertex2d(xx+c*r,yy+s*r);
    }
    glEnd();
    
    glColor3d(0.0,0.0,0.0);
    //glasses
    glBegin(GL_QUADS);
    glVertex2i(x-25,y-52.5);
    glVertex2i(x-25,y-57.5);
    glVertex2i(x-30,y-57.5);
    glVertex2i(x-30,y-52.5);
    
    //glasses
    glBegin(GL_QUADS);
    glVertex2i(x+25,y-52.5);
    glVertex2i(x+25,y-57.5);
    glVertex2i(x+30,y-57.5);
    glVertex2i(x+30,y-52.5);
    glEnd();
    
    
    //sleeves
    glColor3d(0.0,0.0,1.0);
    glBegin(GL_QUADS);
    
    glVertex2i(x+20,y-10);
    glVertex2i(x+20,y-15);
    glVertex2i(x+30,y-20);
    glVertex2i(x+30,y-15);
    
    glVertex2i(x-20,y-10);
    glVertex2i(x-20,y-15);
    glVertex2i(x-30,y-20);
    glVertex2i(x-30,y-15);
    
    //legs
    glColor3d(0.0,0.0,1.0);
    glVertex2i(x-2,y+45);
    glVertex2i(x-2,y+55);
    glVertex2i(x-12,y+55);
    glVertex2i(x-12,y+45);
    
    glColor3d(0.0,0.0,1.0);
    glVertex2i(x+2,y+45);
    glVertex2i(x+2,y+55);
    glVertex2i(x+12,y+55);
    glVertex2i(x+12,y+45);
    
    // shoes
    glColor3d(0.0,0.0,0.0);
    glVertex2i(x+2,y+55);
    glVertex2i(x+2,y+60);
    glVertex2i(x+15,y+60);
    glVertex2i(x+15,y+55);
    
    glColor3d(0.0,0.0,0.0);
    glVertex2i(x-2,y+55);
    glVertex2i(x-2,y+60);
    glVertex2i(x-15,y+60);
    glVertex2i(x-15,y+55);
    
    glColor3d(1.0,0.95,0.0);
    glVertex2i(x-30,y-20);
    glVertex2i(x-45,y+15);
    glVertex2i(x-40,y+15);
    glVertex2i(x-25,y-20);
    
    glVertex2i(x+30,y-20);
    glVertex2i(x+45,y+15);
    glVertex2i(x+40,y+15);
    glVertex2i(x+25,y-20);
    glEnd();

}

Unicorn::Unicorn(){}
Unicorn::~Unicorn(){}
void Unicorn::drawCharacter(int x, int y, int direction){

    
    double xx=(double)(x);
    double yy=(double)(y-45);
    double r=22;
    
    glColor3d(1.0,0.0,0.0);
    glBegin(GL_TRIANGLE_FAN);
    for(int a=0; a<64; ++a)
    {
        const double radian=YsPi*2.0*(double)a/64.0;
        const double c=cos(radian);
        const double s=sin(radian);
        
        //glVertex2d(xx+c*r,yy+s*r);
        glVertex2d(xx+c*r,yy+s*r);
    }
    glEnd();
    
    //hands
    
    xx=(double)(x-21);
    yy=(double)(y+30);
    r=5;
    
    glColor3d(1.0,0.0,0.0);
    glBegin(GL_TRIANGLE_FAN);
    for(int a=0; a<64; ++a)
    {
        const double radian=YsPi*2.0*(double)a/64.0;
        const double c=cos(radian);
        const double s=sin(radian);
        
        //glVertex2d(xx+c*r,yy+s*r);
        glVertex2d(xx+c*r,yy+s*r);
    }
    glEnd();
    
    xx=(double)(x+21);
    yy=(double)(y+30);
    r=5;
    
    glColor3d(1.0,0.0,0.0);
    glBegin(GL_TRIANGLE_FAN);
    for(int a=0; a<64; ++a)
    {
        const double radian=YsPi*2.0*(double)a/64.0;
        const double c=cos(radian);
        const double s=sin(radian);
        
        //glVertex2d(xx+c*r,yy+s*r);
        glVertex2d(xx+c*r,yy+s*r);
    }
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3i(1.0,1.0,1.0);
    //torso
    glVertex2i(x-20,y-30);
    glVertex2i(x-20,y+30);
    glVertex2i(x+20,y+30);
    glVertex2i(x+20,y-30);
    glEnd();
    
    //bottom
    glBegin(GL_QUADS);
    glVertex2i(x-18,y+30);
    glVertex2i(x-18,y+50);
    glVertex2i(x+18,y+50);
    glVertex2i(x+18,y+30);
    glEnd();
    
    //feet
    glBegin(GL_QUADS);
    glVertex2i(x-18,y+50);
    glVertex2i(x-23,y+60);
    glVertex2i(x,y+60);
    glVertex2i(x,y+50);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2i(x+18,y+50);
    glVertex2i(x+23,y+60);
    glVertex2i(x,y+60);
    glVertex2i(x,y+50);
    glEnd();
    
    
    //hand
    glBegin(GL_QUADS);
    glColor3d(1.0,0.0,0.0);
    glVertex2i(x-23,y-30);
    glVertex2i(x-29,y+30);
    glVertex2i(x-20,y+30);
    glVertex2i(x-20,y-30);
    glEnd();
    
    //hand
    glBegin(GL_QUADS);
    glColor3d(1.0,0.0,0.0);
    glVertex2i(x+23,y-30);
    glVertex2i(x+29,y+30);
    glVertex2i(x+20,y+30);
    glVertex2i(x+20,y-30);
    glEnd();
}

Einstein::Einstein(){}
Einstein::~Einstein(){}
void Einstein::drawCharacter(int x, int y, int direction){
    glColor3d(0.65,0.2,0.2);
    glBegin(GL_QUADS);
    
    //tank body
    glVertex2i(x-pow(-1.0,direction)*40,y-40);
    glVertex2i(x-pow(-1.0,direction)*40,y+30);
    glVertex2i(x+pow(-1.0,direction)*40,y+30);
    glVertex2i(x+pow(-1.0,direction)*40,y-30);
    
    glVertex2i(x+pow(-1.0,direction)*40,y-20);
    glVertex2i(x+pow(-1.0,direction)*40,y-25);
    glVertex2i(x+pow(-1.0,direction)*80,y-35);
    glVertex2i(x+pow(-1.0,direction)*80,y-40);
    
    glVertex2i(x-pow(-1.0,direction)*20,y+30);
    glVertex2i(x-pow(-1.0,direction)*20,y+32.5);
    glVertex2i(x+pow(-1.0,direction)*20,y+32.5);
    glVertex2i(x+pow(-1.0,direction)*20,y+30);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex2i(x-pow(-1.0,direction)*20,y+32.5);
    glVertex2i(x+pow(-1.0,direction)*20,y+32.5);
    glVertex2i(x+pow(-1.0,direction)*60,y+32.5);
    glVertex2i(x+pow(-1.0,direction)*60,y+50);
    glVertex2i(x-pow(-1.0,direction)*60,y+50);
    glVertex2i(x-pow(-1.0,direction)*60,y+40);
    glEnd();
    

    
    double xx=(double)(x-45);
    double yy=(double)(y+55);
    
    double xxp=(double)(x+45);
    double yyp=(double)(y+55);
    
    double r=10.0;
    
    glBegin(GL_TRIANGLE_FAN);
    for(int a=0; a<64; ++a)
    {
        const double radian=YsPi*2.0*(double)a/64.0;
        const double c=cos(radian);
        const double s=sin(radian);
        
        glVertex2d(xx+c*r,yy+s*r);
        //glVertex2d(xxp+c*r,yyp+s*r);
    }
    glEnd();
    
    
    glBegin(GL_TRIANGLE_FAN);
    for(int a=0; a<64; ++a)
    {
        const double radian=YsPi*2.0*(double)a/64.0;
        const double c=cos(radian);
        const double s=sin(radian);
        
        //glVertex2d(xx+c*r,yy+s*r);
        glVertex2d(xxp+c*r,yyp+s*r);
    }
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2i(x-45,y+45);
    glVertex2i(x-45,y+65);
    glVertex2i(x+45,y+65);
    glVertex2i(x+45,y+45);
    glEnd();
}
