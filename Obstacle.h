#ifndef SHOOT_3_CLASS_H_IS_INCLUDED
#define SHOOT_3_CLASS_H_IS_INCLUDED
#include "fssimplewindow.h"
#include "yspng.h"
#include "yspngenc.h"
#include "Weapons.h"
#include "player.h"
class Obstacle
{
public:
    int x;
    int y;
    int size;
    double countdown;
    double speed;
    bool direction;
    GLuint thunder1;
    GLuint light;
    void Initial(void);
    void read(void);
    void Draw(double px,double py);
    void Move();
    void CheckCollision(double x,double y);
    bool state;
    void Run(Bullet bullet, Player player);
};

#endif