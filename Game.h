
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yspng.h"

#ifndef Header_h
#define Header_h

struct Coordinates
{
    double x;
    double y;
};

enum WeaponType
{
    DEFAULT,
    NINE_MM,
    CANNON,
    LAND_ROCKET,
    NUCLEAR_ROCKET,
    CAT,
    WATER_BALLOON,
};

class Bullet
{
    bool State;
    double Grav; // It can be varied for various weapons
    int InitSpeed; //The speed of the bullet.
    WeaponType Type; // This will cover geometry of the bullet, particle
    //(line, circle or missile) or line(light line)
    int Life;
    Coordinates Position;
    Coordinates Velocity; //(to take the direction)
    int Angle;
public:
    Bullet();
    ~Bullet();
    Bullet(WeaponType Type); //Constructor based on weaponType
    
    //Functionality
    void Init(WeaponType Type);
    void Run(void);
    void GetInitialVelocity(Coordinates Pos, int Inclination); //This sets the initial position and the initial velocity
    void Draw(void);
    void Move(void); //Moves the bullet based on the gravity and changes the orientation
    void SetState(bool State); //Checks the modifies the state of the bullet
    void ChangeLife (void);
    int GetLife(void);
    
    //Retrive Information
    bool GetState(void); //Return the state of the bullet
    double y(void)const; //Return position y
    double x(void)const; //Return position x
    Coordinates Pos(void); // Return coordinates od position // to call Bullet.Pos.x()
    Coordinates Vel(void); // Return coordinates od position // to call Bullet.Pos.y()
};

class Weapon
{
protected:
    WeaponType Type;
    Coordinates Position;
    int Angle; //It is in degrees
    int NumberOfBullets;
    int Level; //(could be from 1 to 5)
    Bullet Bulls;
    //std::vector<Bullet> Bull;
public:
    Weapon();
    ~Weapon();
    Weapon(WeaponType Type);
    
    //Functionality
    void Initial(WeaponType Type);
    void Run(int key);
    void DrawWeapon(void);
    void SetAngle(int Angle);
    void ChangeAngle( int Delta );
    void Move(Coordinates Delta); //Add delta to actual position.
    void Shot(Coordinates BulletInitPos);
    
    //Get information
    int GetLevel(void);
    int GetBullets(void);
    void ReduceBullet(void);
    double y(void)const; //Return position y
    double x(void)const; //Return position x
    Coordinates Pos(void); // Return coordinates od position // to call Bullet.Pos.x()
    Coordinates Vel(void); // Return coordinates od position // to call Bullet.Pos.y()
    Bullet* GetBullet(void); //Returns bulls
};


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

class Background
{
protected:
    double boundaryX1;
    double boundaryX2;
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
    Background();
    ~Background();
};

class Character /* abstract class */
{
public:
    Character();
    ~Character();
    virtual void drawCharacter(int x, int y, int direction) = 0;
};

class Tank: public Character{
public:
    Tank();
    ~Tank();
    void drawCharacter(int x, int y, int direction);
};
class Unicorn: public Character{
public:
    Unicorn();
    ~Unicorn();
    void drawCharacter(int x, int y, int direction);
};
class Einstein: public Character{
public:
    Einstein();
    ~Einstein();
    void drawCharacter(int x, int y, int direction);
};


#define TYPESOFWEAPONS 6
class Player{
private:
    int X, Y, direction;
    int money;
    /* weaponList[weapon#] = level
     * level 0 means player doesn't own that weapon yet */
    int weaponList[TYPESOFWEAPONS];
    int myCharacter;
    char userfile[50];
public:
    Player();
    Player(int initX, int initY);
    ~Player();
    void playerSet(int initX, int initY);
    void movePlayer();
    void drawPlayer();
    int getX();
    int getY();
    int getDirection();
    void ReadProperties(char *username);
    void SaveProperties();
    void setMyCharacter(int character);
    int getMyCharacter();
    int *getWeaponList();
    void setWeaponList(int index, int level);
    int getMoney();
    void setMoney(int newMoney);
    void Initial();
    void Run();
};

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
    void Initial(int X,int Y,int Size,int Direction,int Speed);
    void read(void);
    void Draw(double px,double py);
    void Move();
    void CheckCollision(double x,double y);
    bool state;
    void Run(Weapon &weapon,Player &player);
};



class Game
{
public:
    Background background;
    Obstacle obstacle1;
    Obstacle obstacle2;
    Weapon weapon;
    Bullet bullet;
    Player player;
    void Initial(void);
    void Run(int &status);
};

#endif /* Header_h */
