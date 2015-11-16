// This file is in charge to control weapon behavior and bullet. 

#include "fssimplewindow.h" 
#include "Weapons.h"
#include<math.h>
#define PI 3.14159265


////////////////////////////////////////////////////////////////////////////////
// Weapon Class  

Weapon::Weapon()
{

}

Weapon::~Weapon()
{

}

Weapon::Weapon(WeaponType Type)
{

}

void Weapon::DrawWeapon(void)
{
	double length = 10;
	glColor3ub(255, 0, 0);
	glBegin(GL_LINES);
	glVertex2d(Position.x, Position.y);
	glVertex2d(Position.x*(1 + cos(Angle*PI/180)), Position.y*(1 + sin(Angle*PI/180)));
	glEnd();
}

void Weapon::SetAngle(double Angle)
{
	this->Angle = Angle;
}

//Add delta to actual position.
void Weapon::Move(Coordinates Delta) 
{
	Position.x += Delta.x;
	Position.y += Delta.y;
}

int Weapon::GetLevel(void)
{
	return this->Level;
}

int Weapon::GetBullets(void)
{
	return this->NumberOfBullets;
}

void Weapon::ReduceBullet(void)
{
	if (this->NumberOfBullets > 0)
	{
		this->NumberOfBullets--;
	}
}

////////////////////////////////////////////////////////////////////////////////
// Bullet Class

Bullet::Bullet() {

}

Bullet::~Bullet() {

}

//Constructor based on weaponType
Bullet::Bullet(WeaponType Type) {

}
//This sets the initial position and the initial velocity
void Bullet::GetInitialVelocity(Coordinates Position, double Inclination) {

}

void Bullet::Draw(void) {

}

//Moves the bullet based on the gravity and changes the orientation
void Bullet::Move(void) {

}

//Checks the modifies the state of the bullet
void Bullet::SetState(bool State) {

}

