# include <stdio.h>
# include "fssimplewindow.h"

struct Coordinates
{
	double x;
	double y;
};

enum WeaponType
{
	NINE_MM,
	CANNON,
	LAND_ROCKET,
	NUCLEAR_ROCKET,
	CAT,
	WATER_BALLOON,
};

class Weapon
{
protected:
	WeaponType Type;
	Coordinates Position;
	double Angle; //It is in degrees
	int NumberOfBullets;
	int Level; //(could be from 1 to 5)
	Bullet Bulls;
public:
	Weapon();
	~Weapon();
	Weapon(WeaponType Type);
	void DrawWeapon(void);
	void SetAngle(double Angle);
	void Move(Coordinates Delta); //Add delta to actual position.
	int GetLevel(void);
	int GetBullets(void);
	void ReduceBullet(void);
};

class Bullet
{
	bool State;
	double Grav; // It can be varied for various weapons
	WeaponType Type; // This will cover geometry of the bullet, particle
					 //(line, circle or missile) or line(light line)
	Coordinates Position;
	Coordinates Velocity; //(to take the direction)
	double Angle;
public:
	Bullet();
	~Bullet();
	Bullet(WeaponType Type); //Constructor based on weaponType
	void GetInitialVelocity(Coordinates Position, double Inclination); //This sets the initial position and the initial velocity
	void Draw(void);
	void Move(void); //Moves the bullet based on the gravity and changes the orientation
	void SetState(bool State); //Checks the modifies the state of the bullet
};