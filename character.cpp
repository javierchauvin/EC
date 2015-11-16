//
//  character.cpp
//  FINAL PROJECT
//
//  Created by Kelly Cheng on 11/16/15.
//  Copyright © 2015 Kelly Cheng. All rights reserved.
//

#include "character.h"
#include "fssimplewindow.h"


Character::Character(){}
Character::~Character(){}

Tank::Tank(){}
Tank::~Tank(){}
void Tank::drawCharacter(int x, int y){
    int w = 5;
    glColor3ub(0,0,255);
    glBegin(GL_QUADS);
    glVertex2i(x-w, y-w); // top left
    glVertex2i(x+w, y-w); // top right
    glVertex2i(x+w, y+w); // bottom right
    glVertex2i(x-w, y+w); // bottom left
    glEnd();
}

Unicorn::Unicorn(){}
Unicorn::~Unicorn(){}
void Unicorn::drawCharacter(int x, int y){
    int w = 5;
    glColor3ub(0,255,0);
    glBegin(GL_QUADS);
    glVertex2i(x-w, y-w); // top left
    glVertex2i(x+w, y-w); // top right
    glVertex2i(x+w, y+w); // bottom right
    glVertex2i(x-w, y+w); // bottom left
    glEnd();
}

Einstein::Einstein(){}
Einstein::~Einstein(){}
void Einstein::drawCharacter(int x, int y){
    int w = 5;
    glColor3ub(255,0,0);
    glBegin(GL_QUADS);
    glVertex2i(x-w, y-w); // top left
    glVertex2i(x+w, y-w); // top right
    glVertex2i(x+w, y+w); // bottom right
    glVertex2i(x-w, y+w); // bottom left
    glEnd();
}
