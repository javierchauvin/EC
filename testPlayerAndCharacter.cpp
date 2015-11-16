//
//  main.cpp
//  PS03
//
//  Created by Kelly Cheng on 11/16/15.
//  Copyright © 2015 Kelly Cheng. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "fssimplewindow.h"
#include "player.h"

#define TYPESOFWEAPONS 3
#define TANK 0
#define UNICORN 1
#define EINSTEIN 2

int main(void)
{
    int terminate = 0;
    Player player1;
    //player1.ReadProperties();
    FsOpenWindow(16,16,800,600,1);
    
    while (terminate == 0){
        FsPollDevice();
        int key = FsInkey();
        switch(key)
        {
            case FSKEY_ESC: // terminate the program
                terminate = 1;
                break;
            case FSKEY_SPACE:
                player1.setMyCharacter(UNICORN);
                break;
        }
        player1.movePlayer(key);
        
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        player1.drawPlayer();
        FsSwapBuffers();
        FsSleep(25);
    }
    return 0;
    
}