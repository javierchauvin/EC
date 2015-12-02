#include "Game.h"

void Obstacle::Initial(int X,int Y,int Size,int Direction,int Speed)
{
    read();
    x=X;
    y=Y;
    size=Size;
    direction=Direction;
    speed=Speed;
    state1=0;
    state2=0;
    hstate1=0;
    hstate2=0;
    countdown=0;
}


void Obstacle::read()
{
    
    char fn1[256]="Thunder.png";
    char fn2[256]="lightning.png";
    YsRawPngDecoder png[2];
    png[0].Decode(fn1);
    png[1].Decode(fn2);
    //gl
    //FsOpenWindow(16,16,800,600,1);
    GLuint texId[2];
    // glGenTextures(2,texId);  // You can also reserve two texture identifies with one call this way
    glGenTextures(1,&texId[0]);  // Reserve one texture identifier
    glBindTexture(GL_TEXTURE_2D,texId[0]);  // Making the texture identifier current (or bring it to the deck)
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    
    glTexImage2D
    (GL_TEXTURE_2D,
     0,    // Level of detail
     GL_RGBA,
     png[0].wid,
     png[0].hei,
     0,    // Border width, but not supported and needs to be 0.
     GL_RGBA,
     GL_UNSIGNED_BYTE,
     png[0].rgba);
    
    glGenTextures(1,&texId[1]);  // Reserve one texture identifier
    glBindTexture(GL_TEXTURE_2D,texId[1]);  // Making the texture identifier current (or bring it to the deck)
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    
    glTexImage2D
    (GL_TEXTURE_2D,
     0,    // Level of detail
     GL_RGBA,
     png[1].wid,
     png[1].hei,
     0,    // Border width, but not supported and needs to be 0.
     GL_RGBA,
     GL_UNSIGNED_BYTE,
     png[1].rgba);
    
    thunder1=texId[0];
    light=texId[1];
}
void Obstacle::Draw(double p1x,double p1y,double p2x,double p2y)
{
    int wid=800,hei=600;
    glViewport(0,0,wid,hei);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,(float)wid-1,(float)hei-1,0,-1,1);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glColor4d(1.0,1.0,1.0,1.0);
    
    
    //first
    //    if (state==0) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,thunder1);
    
    glBegin(GL_QUADS);
    
    glTexCoord2d(0.0,0.0);
    glVertex2i(x,y);
    
    glTexCoord2d(1.0,0.0);
    glVertex2i(x+size,y);
    
    glTexCoord2d(1.0,1.0);
    glVertex2i(x+size,y+size);
    
    glTexCoord2d(0.0,1.0);
    glVertex2i(x,y+size);
    glEnd();
    glDisable(GL_BLEND);
    
    //    }
    
    if (state1==1) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0,(float)wid-1,(float)hei-1,0,-1,1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
        
        //        glEnable(GL_BLEND);
        //        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glColor4d(1.0,1.0,1.0,1.0);
        
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,light);
        glBegin(GL_QUADS);
        
        glTexCoord2d(0.0,0.0);
        glVertex2i(x,y);
        
        glTexCoord2d(1.0,0.0);
        glVertex2i(x+size,y);
        
        glTexCoord2d(1.0,1.0);
        glVertex2i(p1x,p1y);
        
        glTexCoord2d(0.0,1.0);
        glVertex2i(p1x,p1y+size);
        glEnd();
        //        glDisable(GL_BLEND);
        
    }
    if (state2==1) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0,(float)wid-1,(float)hei-1,0,-1,1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
        
        //        glEnable(GL_BLEND);
        //        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glColor4d(1.0,1.0,1.0,1.0);
        
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,light);
        glBegin(GL_QUADS);
        
        glTexCoord2d(0.0,0.0);
        glVertex2i(x,y);
        
        glTexCoord2d(1.0,0.0);
        glVertex2i(x+size,y);
        
        glTexCoord2d(1.0,1.0);
        glVertex2i(p2x,p2y);
        
        glTexCoord2d(0.0,1.0);
        glVertex2i(p2x,p2y+size);
        glEnd();
        //        glDisable(GL_BLEND);
        
    }
}


void Obstacle::Move()
{
    if (direction==1)
    {
        x+=speed;
    }
    else if (direction==0)
        x-=speed;
    
    if (x<0&& direction==0) {
        direction=1;
    }
    else if (x>640&&direction==1) {
        direction=0;
    }
}
void Obstacle::CheckCollision(double b1x,double b1y,double b2x,double b2y)
{
    if(x<=b1x && b1x<x+size && y<=b1y && b1y<y+size*0.8)
    {
        state1=1;
        hstate1=1;
    }
    if(x<=b2x && b2x<x+size && y<=b2y && b2y<y+size*0.8)
    {
        state2=1;
        hstate2=1;
    }
}
void Obstacle::Run(Weapon &weapon1,Player &player1,Weapon &weapon2,Player &player2)
{
    double b1x=weapon1.GetBullet()->x();
    double b1y=weapon1.GetBullet()->y();
    int p1x=player1.getX();
    int p1y=player1.getY();
    double b2x=weapon2.GetBullet()->x();
    double b2y=weapon2.GetBullet()->y();
    int p2x=player2.getX();
    int p2y=player2.getY();
    Draw(p1x,p1y,p2x,p2y);
    Move();
    CheckCollision(b1x,b1y,b2x,b2y);
    if (hstate1==1) {
        player1.health-=1.5;
        hstate1=0;
    }
    if (hstate2==1) {
        player2.health-=1.5;
        hstate2=0;
    }
    if (state1==1)
    {
        countdown+=0.9;
        if (countdown>1.2)
        {
            state1=0;
            countdown=0;
        }
    }
    if (state2==1)
    {
        countdown+=0.9;
        if (countdown>1.2)
        {
            state2=0;
            countdown=0;
        }
    }
}