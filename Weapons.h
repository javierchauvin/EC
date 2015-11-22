
#ifndef WEAPONS_H_IS_INCLUDED
#define WEAPONS_H_IS_INCLUDED

#include <stdio.h>
//#include <vector>
#include "fssimplewindow.h"
#include "player.h"

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
    void Init(WeaponType Type);
	void Run(int key, Player P);
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
};

#endif