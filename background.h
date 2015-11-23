//
//  Header.h
//  framework
//
//  Created by Chris Wang on 11/20/15.
//  Copyright © 2015 24780. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yspng.h"
#include "Weapons.h"
#ifndef Header_h
#define Header_h

class MountainCube
{
protected:
    double x,y;
    
public:
    int state;
    MountainCube();
    double GetX();
    double GetY();
    void draw();
    void MakeFromString(char str[]);
};

class background
{
protected:
    double boundaryX1=200;
    double boundaryX2=600;
public:
    int nCube;
    int w,h;
    double GetBoundaryX1();
    double GetBoundaryX2();
    MountainCube* CubePtr;
    void cleanup();
    void DrawMountain(void);
    void Initial(void);
    void Run(Weapon &gun);
    bool checkcollision();
    void DrawBackground(void);
    void ReadBackground(void);
    void MakeFromString(char str[]);
    void ReadFile();
    void checkcollision(Weapon &gun);
    YsRawPngDecoder decoder;
    background();
    ~background();
};


#endif /* Header_h */
