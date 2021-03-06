
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
    bool status; //0:not my turn 1:my turn
    //int hit; //0:not hit
    int money;
    /* weaponList[weapon#] = level
     * level 0 means player doesn't own that weapon yet */
    int weaponList[TYPESOFWEAPONS];
    int weapontype;
    int myCharacter;
    char userfile[50];
public:
    double health;
    Player();
    Player(int initX, int initY);
    ~Player();
    void playerSet(int initX, int initY);
    void movePlayer(int key);
    void drawPlayer();
    int hit; //0:not hit
    int getX();
    int getY();
    int getDirection();
    void ReadProperties(const char *username);
    void SaveProperties();
    void setMyCharacter(int character);
    int getMyCharacter();
    int *getWeaponList();
    void setWeaponList(int index, int level);
    int getMoney();
    void setMoney(int newMoney);
    void Initial(int x, int y, int dir, int Status);
    void Run(int key);
    void DrawMyTurn();
    void setHealth();
    void DrawHealth();
    bool getStatus();
    void setStatus(bool state);
    
};

class Bullet
{
    bool State;
	bool IsShoot;
    double Grav; // It can be varied for various weapons
    int InitSpeed; //The speed of the bullet.
    WeaponType Type; // This will cover geometry of the bullet, particle
    //(line, circle or missile) or line(light line)
    int Life;
	int LifeInitValue; 
    Coordinates Position;
    Coordinates Velocity; //(to take the direction)
    int Angle;
	int Radius;
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
	void CheckScreen(void);
	void ChangeSpeed(int Delta);
	void SetLife( int Level );
	void Shoot (bool IsS);
	bool GetIsShoot (void);
	void SetType( WeaponType Type );
    
    //Retrive Information
    bool GetState(void); //Return the state of the bullet
    double y(void)const; //Return position y
    double x(void)const; //Return position x
    Coordinates Pos(void); // Return coordinates od position // to call Bullet.Pos.x()
    Coordinates Vel(void); // Return coordinates od position // to call Bullet.Pos.y()
	double GetRadius(void); //Return the radius of the bullet
};

class Weapon
{
protected:
	bool State;
    WeaponType Type;
    int WeaponTypeNum;
    Coordinates Position;
    int Angle; //It is in degrees
    int NumberOfBullets;
    int Level; //(could be from 1 to 5)
    Bullet Bulls;
    //std::vector<Bullet> Bull;
	GLuint Weapon_Picture;
public:
    Weapon();
    ~Weapon();
    //Weapon(WeaponType Type);
    
    //Functionality
    void Initial(WeaponType Type, bool st,Player &player);
    void SetWeapon(WeaponType Type,Player &player);
    void Run(int key, Player &player);
    void DrawWeapon(void);
    void SetAngle(int Angle);
    void ChangeAngle( int Delta );
    void Move(Coordinates Delta); //Add delta to actual position.
    void Shot(Coordinates BulletInitPos);
	void Read_Image();
	void Check( WeaponType Type, int Lev );
    
    //Get information
    int GetLevel(void);
    int GetBullets(void);
    void ReduceBullet(void);
	void SetState(bool st);
	bool GetWeaponState( void );
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
    double GetBoundaryX1();
    double GetBoundaryX2();
    MountainCube* CubePtr;
    void cleanup();
    void DrawMountain(void);
    void Initial(void);
    void Run(Weapon &gun1,Weapon &gun2);
    void DrawBackground(void);
    void ReadBackground(void);
    void MakeFromString(char str[]);
    void ReadFile();
    void checkcollision(Weapon &gun1,Weapon &gun2);
    YsRawPngDecoder decoder;
    Background();
    ~Background();
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
    void Draw(double p1x,double p1y,double p2x,double p2y);
    void Move();
    void CheckCollision(double b1x,double b1y,double b2x,double b2y);
    bool state1;
    bool state2;
    bool hstate1;
    bool hstate2;
    void Run(Weapon &weapon1,Player &player1,Weapon &weapon2,Player &player2);
};

class Game
{
public:
    Background background;
    Obstacle obstacle1;
    Obstacle obstacle2;
    Bullet bullet;
    Weapon weapon1;
    Weapon weapon2;
    void Initial(Player &PlayerOne,Player &PlayerTwo);
    void Run(int &status,Player &PlayerOne,Player &PlayerTwo);
};

void checkCollision(Player &player1, Player &player2, Weapon &weapon1, Weapon
                    &weapon2);

#endif /* Header_h */
