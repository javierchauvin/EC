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


Character::Character(){}
Character::~Character(){}

Tank::Tank(){}
Tank::~Tank(){}
void Tank::drawCharacter(int x, int y, int direction){
    
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
    
    const double YsPi=3.1415927;
    
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

Unicorn::Unicorn(){}
Unicorn::~Unicorn(){}
void Unicorn::drawCharacter(int x, int y, int direction){
    const double YsPi=3.1415927;
    
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
    int w = 5;
    glColor3ub(255,0,0);
    glBegin(GL_QUADS);
    glVertex2i(x-w, y-w); // top left
    glVertex2i(x+w, y-w); // top right
    glVertex2i(x+w, y+w); // bottom right
    glVertex2i(x-w, y+w); // bottom left
    glEnd();
}
