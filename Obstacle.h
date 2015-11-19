#ifndef SHOOT_3_CLASS_H_IS_INCLUDED
#define SHOOT_3_CLASS_H_IS_INCLUDED
#include "fssimplewindow.h"
#include "shoot-4-class.h"
#include "yspng.h"
#include "yspngenc.h"
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
    void read(void);
    void Draw(double px,double py);
    void Move();
    void CheckCollision(double x,double y);
    bool state;
    void Run(double x,double y, double px, double py);
};

#endif
