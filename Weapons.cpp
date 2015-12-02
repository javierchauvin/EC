// This file is in charge to control weapon behavior and bullet. 

#include<math.h>
#include "Game.h"

#define PI 3.14159265


double D2Rad ( int degrees ){
	return degrees*PI / 180;
}

////////////////////////////////////////////////////////////////////////////////
// Weapon Class  

Weapon::Weapon(){}
Weapon::~Weapon(){}

//Weapon::Weapon(void/*WeaponType Type*/)
//{
//	//Initial(Type,true);
//}

void Weapon::Initial(WeaponType WType, bool st){

	State = st;
	Type = WType;
    Angle = 0; 
    NumberOfBullets = 10;//For now 
    Level = 5; //ForNow
    Bulls.Init(WType);
}
bool Weapon::GetWeaponState()
{
    return State;
}

void Weapon::Run(int key, Player &player)
{
	if (State){
		Position.x = player.getX()+80;
		Position.y = player.getY()-37;

		if(FSKEY_LEFT==key){
			ChangeAngle(-10);
		}
		if(FSKEY_RIGHT==key){
			ChangeAngle(10);	
		}
		if(FSKEY_SPACE==key){
			Shot(Position);
		}

		if(Bulls.GetState()){
			Bulls.Move();
			Bulls.Draw();
		}
		DrawWeapon();
	}
}

void Weapon::Shot(Coordinates BulletInitPos){

	//Bullet B;
	//B.Init(Type);
	//Bull.push_back(Type);
	Bulls.GetInitialVelocity(BulletInitPos,Angle);
}

void Weapon::ChangeAngle( int Delta ){
	if(Angle < -180){
		Angle += 360;
	}
	if(180 < Angle){
		Angle -= 360;
	}
	Angle += Delta;
	//printf("Angle: %d\n",Angle);
}

void Weapon::DrawWeapon(void)
{
	switch(Type){
	case NINE_MM:
	break;

	case CANNON:
		break;

	case LAND_ROCKET:
		break;

	case NUCLEAR_ROCKET:
		break;

	case CAT:
		break;

	case WATER_BALLOON:{
		break;
	}

	case DEFAULT:{
		const double TubeLong = 20; 

		Coordinates Center;
		Center.x = Position.x;
		Center.y = Position.y;

		Coordinates End;
		End.x = Center.x + cos(D2Rad(Angle)) * TubeLong;
		End.y = Center.y + sin(D2Rad(Angle)) * TubeLong;

		//coor2scr(&Center);
		//coor2scr(&End);

		glColor3ub(0,0,255);
		glBegin(GL_LINES);
		glVertex2d( Center.x, Center.y ); 
		glVertex2d( End.x, End.y );  
		glEnd();
		break;
		}
	}
}

void Weapon::SetAngle(int Angle)
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

Bullet* Weapon::GetBullet(void){
	return &Bulls;
}

////////////////////////////////////////////////////////////////////////////////
// Bullet Class

Bullet::Bullet(){
	State = true;
	Grav = 9.8; // It can be varied for various weapons
	Type = DEFAULT;
	InitSpeed = 100;
	Velocity.x = 0;
	Velocity.y = 0;
}
Bullet::~Bullet() {}

//Initializes the bullet characteristics depending on the weapon type
//By default the weapon is 9mm.
Bullet::Bullet(WeaponType Type) {
	Init(Type);
}

void Bullet::Init(WeaponType Type){

	Position.x = 0;
	Position.y = 0;
	Velocity.x = 0;
	Velocity.y = 0;

	switch(Type){
		case NINE_MM:
			 break;

		case CANNON:
			break;

		case LAND_ROCKET:
			break;

		case NUCLEAR_ROCKET:
			break;

		case CAT:
			break;

		case WATER_BALLOON:
			break;

		case DEFAULT:
			State = true;
			Grav = 9.8; // It can be varied for various weapons
			Type = DEFAULT;
			Life = 10;
			InitSpeed = 500;
		break;
    }
}

//This sets the initial position and the initial velocity
void Bullet::GetInitialVelocity(Coordinates Pos, int Inclination) {
	Velocity.x = cos(D2Rad(Inclination)) * InitSpeed;
	Velocity.y = sin(D2Rad(Inclination)) * InitSpeed;

	Position = Pos;
}

void Bullet::Draw(void) {

		switch(Type){
		case NINE_MM:
			 break;

		case CANNON:
			break;

		case LAND_ROCKET:
			break;

		case NUCLEAR_ROCKET:
			break;

		case CAT:
			break;

		case WATER_BALLOON:
			break;

		case DEFAULT:
			double x = Position.x;
			double y = Position.y;
			double r = 4; //Fixed size for now- will change this later based on weapon type

			glColor3ub(255,0,0);
			if (State){
				glBegin(GL_TRIANGLE_FAN);
				for (int a = 0; a < 64; ++a)
				{
					const double radian = PI*2.0*(double)a / 64.0;
					const double c = cos(radian);
					const double s = sin(radian);

					glVertex2d(x + c*r, y + s*r);
				}
				glEnd();
			}
		break;
    }

}

//Moves the bullet based on the gravity and changes the orientation
void Bullet::Move(void) {
    double dt = 0.025; //The speed of the bullet is same for all weapons- this can be changed on weapon type
    
    if (State)
    {
        Position.x += Velocity.x*dt;
        Position.y += Velocity.y*dt;

        double ax = 0;
        double ay = Grav;

        Velocity.x += ax*dt;
        Velocity.y += ay*dt;
    }
}

//Checks the modifies the state of the bullet
void Bullet::SetState(bool State) {
    this->State = State;
    //reset bullet position to default values
    if (State == false){
        Position.x = 0;
        Position.y = 0;
    }
}

//Return position y //Bullet.x();
double Bullet::y(void)const{
    return Position.y;
} 
//Return position x ////Bullet.y();
double Bullet::x(void)const{
    return Position.x;
}
// Return coordinates od position // to call Bullet.Pos.x()
Coordinates Bullet::Pos(void){
    return Position;
}

// Return coordinates od position // to call Bullet.Pos.y() 
Coordinates Bullet::Vel(void){
    return Velocity;
} 

void Bullet::ChangeLife (void){
	Life -= 1;
	if( Life <= 0){
		State = false;
	}
}

bool Bullet::GetState(void){
	return State;
}

int Bullet::GetLife(void){
    return Life;
}
