//
//  character.h
//  FINAL PROJECT
//
//  Created by Kelly Cheng on 11/16/15.
//  Copyright © 2015 Kelly Cheng. All rights reserved.
//

#ifndef character_h
#define character_h

#include <stdio.h>

class Character /* abstract class */
{
public:
    Character();
    ~Character();
    virtual void drawCharacter(int x, int y) = 0;
};

class Tank: public Character{
public:
    Tank();
    ~Tank();
    void drawCharacter(int x, int y);
};
class Unicorn: public Character{
public:
    Unicorn();
    ~Unicorn();
    void drawCharacter(int x, int y);
};
class Einstein: public Character{
public:
    Einstein();
    ~Einstein();
    void drawCharacter(int x, int y);
};

#endif /* character_h */
