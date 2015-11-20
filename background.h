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

#ifndef Header_h
#define Header_h

class MountainCube
{
public:
    double x,y;
    double boundaryX,boundaryY;
    int state;
    MountainCube();
    void draw();
    void MakeFromString(char str[]);
};

class background
{
public:
    int nCube;
    int w,h;
    MountainCube* CubePtr;
    void cleanup();
    void DrawMountain(void);
    void initial(void);
    void Run(double bx,double by,int level);
    bool checkcollision();
    void DrawBackground(void);
    void ReadBackground(void);
    void MakeFromString(char str[]);
    void ReadFile();
    void checkcollision(double bx,double by,int level);
    YsRawPngDecoder decoder;
    background();
    ~background();
};


#endif /* Header_h */
