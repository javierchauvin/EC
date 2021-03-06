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

void Weapon::Initial(WeaponType WType, bool st,Player &player){

    switch (WType)
    {
        case DEFAULT:
            WeaponTypeNum=0;
            break;
        case NINE_MM:
            WeaponTypeNum=1;
            break;
        case CANNON:
            WeaponTypeNum=2;
            break;
        case LAND_ROCKET:
            WeaponTypeNum=3;
            break;
        case NUCLEAR_ROCKET:
            WeaponTypeNum=4;
            break;
        case CAT:
            WeaponTypeNum=5;
            break;
        case WATER_BALLOON:
            WeaponTypeNum=6;
            break;
        default:
            WeaponTypeNum=7;
            break;
    }
	State = st;
	Type = WType;
    int *WeaponList=player.getWeaponList();
    Read_Image();
	Read_Image();
    Angle = 0; 
    NumberOfBullets = 10;//For now 
    Level = WeaponList[WeaponTypeNum] ; //ForNow
    Bulls.Init(WType);
	Bulls.SetLife(Level);
}
void Weapon::SetWeapon(WeaponType WType, Player &player){
    switch (WType)
    {
        case DEFAULT:
            WeaponTypeNum=0;
            break;
        case NINE_MM:
            WeaponTypeNum=1;
            break;
        case CANNON:
            WeaponTypeNum=2;
            break;
        case LAND_ROCKET:
            WeaponTypeNum=3;
            break;
        case NUCLEAR_ROCKET:
            WeaponTypeNum=4;
            break;
        case CAT:
            WeaponTypeNum=5;
            break;
        case WATER_BALLOON:
            WeaponTypeNum=6;
            break;
        default:
            WeaponTypeNum=7;
            break;
    }

    Type = WType;
	Bulls.SetType(WType);
    int *WeaponList=player.getWeaponList();

    Read_Image();
    NumberOfBullets = 10;//For now
    Level = WeaponList[WeaponTypeNum]; //ForNow
    printf("Weapon %d LEVEL= %d\n",(WeaponTypeNum+1),Level);
    Bulls.Init(WType);
	Bulls.SetLife(Level);
}

bool Weapon::GetWeaponState()
{
    return State;
}

void Weapon::Run(int key, Player &player)
{
	if(player.getX()<400)
	{
		Position.x = player.getX()+45;
		Position.y = player.getY()-15;
	}
	else
	{
		Position.x = player.getX()-45;
		Position.y = player.getY()-15;
	}

	if (State){

		if(FSKEY_DOWN==key){
			ChangeAngle(-10);
		}
		if(FSKEY_UP==key){
			ChangeAngle(10);	
		}
		if(FSKEY_SPACE==key && !Bulls.GetState()){
			Shot(Position);
		}
		if(FSKEY_W==key){
			Bulls.ChangeSpeed(30);
		}
		if(FSKEY_S==key){
			Bulls.ChangeSpeed(-30);
		}

		if(Bulls.GetState()){
			Bulls.CheckScreen();
			Bulls.Move();
			Bulls.Draw();
		}
	}

	DrawWeapon();
}

void Weapon::Shot(Coordinates BulletInitPos){

	Bulls.SetState(true);
	Bulls.Shoot( true );
	Bulls.GetInitialVelocity(BulletInitPos,Angle);
}

void Weapon::Read_Image()
{
	char fn1[256] = "CANNON.png";


	switch (Type)
	{
	case DEFAULT:
		sprintf(fn1, "DEFAULT.png");
		break;
	case NINE_MM:
		sprintf(fn1, "NINE_MM.png");
		break;
	case CANNON:
		sprintf(fn1, "CANNON.png");
		break;
	case LAND_ROCKET:
		sprintf(fn1, "LAND_ROCKET.png");
		break;
	case NUCLEAR_ROCKET:
		sprintf(fn1, "NUCLEAR_ROCKET.png");
		break;
	case CAT:
		sprintf(fn1, "CAT.png");
		break;
	case WATER_BALLOON:
		sprintf(fn1, "WATER_BALLOON.png");
		break;
	default:
		sprintf(fn1, "NINE_MM.png");
		break;
	}

	YsRawPngDecoder png;
	png.Decode(fn1);

	GLuint texId;
	glGenTextures(1, &texId);  // Reserve one texture identifier
	glBindTexture(GL_TEXTURE_2D, texId);  // Making the texture identifier current (or bring it to the deck)

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D
		(GL_TEXTURE_2D,
			0,    // Level of detail
			GL_RGBA,
			png.wid,
			png.hei,
			0,    // Border width, but not supported and needs to be 0.
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			png.rgba);
	Weapon_Picture = texId;
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
	int wid = 800, hei = 600; int size = 40;

	double sizex, sizey;
	double aspect;

	switch (Type)
	{
	case DEFAULT:
		sizex = 20;
		aspect = 0.4;
		break;
	case NINE_MM:
		sizex = 40;
		aspect = 1;
		break;
	case CANNON:
		sizex = 60;
		aspect = 600 / 124;
		break;
	case LAND_ROCKET:
		sizex = 70;
	aspect = 469 / 157;
		break;
	case NUCLEAR_ROCKET:
		sizex = 90;
		aspect = 256 / 128;
		break;
	case CAT:
		sizex = 40;
		break;
	case WATER_BALLOON:
		sizex = 40;
		break;
	default:
		break;
	}

	sizey = sizex/aspect;

	glViewport(0, 0, wid, hei);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Weapon_Picture);

	glBegin(GL_QUADS);

	if (Position.x < 400)
	{
		glTexCoord2d(0.0, 0.0);
		glVertex2d(Position.x+sizey*sin(Angle*PI/180)/2, Position.y-sizey*cos(Angle*PI/180)/2);

		glTexCoord2d(1.0, 0.0);
		glVertex2d(Position.x + sizey*sin(Angle*PI / 180)/2+sizex*cos(Angle*PI/180), Position.y - sizey*cos(Angle*PI / 180)/2+sizex*sin(Angle*PI/180));

		glTexCoord2d(1.0, 1);
		glVertex2d(Position.x + sizex*cos(Angle*PI / 180)-sizey*sin(Angle*PI/180)/2, Position.y + sizex*sin(Angle*PI / 180)+sizey*cos(Angle*PI/180)/2);

		glTexCoord2d(0.0, 1);
		glVertex2d(Position.x - sizey*sin(Angle*PI / 180) / 2, Position.y + sizey*cos(Angle*PI / 180) / 2);
		glEnd();
		glDisable(GL_BLEND);
	}
	else
	{
		glTexCoord2d(1.0, 0.0);
		glVertex2d(Position.x - sizey*sin(Angle*PI / 180)/2 + sizex*cos(Angle*PI / 180), Position.y + sizey*cos(Angle*PI / 180)/2 + sizex*sin(Angle*PI / 180));

		glTexCoord2d(0.0, 0.0);
		glVertex2d(Position.x - sizey*sin(Angle*PI / 180)/2, Position.y + sizey*cos(Angle*PI / 180)/2);

		glTexCoord2d(0.0, 1);
		glVertex2d(Position.x + sizey*sin(Angle*PI / 180) / 2, Position.y - sizey*cos(Angle*PI / 180) / 2);

		glTexCoord2d(1.0, 1);
		glVertex2d(Position.x + sizey*sin(Angle*PI / 180) / 2 + sizex*cos(Angle*PI / 180), Position.y - sizey*cos(Angle*PI / 180) / 2 + sizex*sin(Angle*PI / 180));
		glEnd();
		glDisable(GL_BLEND);
	}
	glDisable(GL_TEXTURE_2D);

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

void Weapon::SetState(bool st){
	State = st;
}

////////////////////////////////////////////////////////////////////////////////
// Bullet Class

Bullet::Bullet(){
	State = false;
	Grav = 9.8; // It can be varied for various weapons
	Type = DEFAULT;
	InitSpeed = 500;
	Velocity.x = 0;
	Velocity.y = 0;
	LifeInitValue = 10;
	Life = LifeInitValue;
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
	State = false;
	IsShoot = false;
	SetType(Type);
	Life = LifeInitValue;
}

void Bullet::SetType( WeaponType Type ){
	
	switch(Type){
		case NINE_MM:
			this->Type = NINE_MM;
			Grav = 9.8; 
			InitSpeed = 400;
			LifeInitValue *= 1;
			Radius = LifeInitValue;
			break;

		case CANNON:
			this->Type = CANNON;
			Grav = 20; 
			InitSpeed = 600;
			Type = CANNON;
			Grav = 50; 
			InitSpeed = 200;
			LifeInitValue *= 3;
			Radius = LifeInitValue;
			break;

		case LAND_ROCKET:
			this->Type = LAND_ROCKET;
			Grav = 60;
			InitSpeed = 250;
			LifeInitValue *= 1.8;
			Radius = LifeInitValue;
			break;

		case NUCLEAR_ROCKET:
			this->Type = NUCLEAR_ROCKET;
			Grav = 10;
			InitSpeed = 200;
			LifeInitValue *= 2;
			Radius = LifeInitValue;
			break;

		case CAT:
			this->Type = CAT;
			Grav = 3; 
			InitSpeed = 300;
			LifeInitValue *= 1;
			Radius = LifeInitValue;
			break;

		case WATER_BALLOON:
			this->Type = WATER_BALLOON;
			Grav = 7; 
			InitSpeed = 400;
			LifeInitValue *= 1;
			Radius = LifeInitValue;
			break;

		case DEFAULT:
			this->Type = DEFAULT;
			Grav = 45; // It can be varied for various weapons
			InitSpeed = 200;
			LifeInitValue *= 1;
			Radius = LifeInitValue;
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

	double x = Position.x;
	double y = Position.y;
	double r;

	if (this->Radius < 3)
	{
		r = 3;
	}
	else
	{
		r = Radius;
	}

		switch(Type){
		case NINE_MM:
			glColor3ub(0, 0, 0);
			if (State) {
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

		case CANNON:
			glColor3ub(144, 120, 130);
			if (State) {
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

		case LAND_ROCKET:
			glColor3ub(148, 20, 20);
			if (State) {
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

		case NUCLEAR_ROCKET:
			glColor3ub(210, 16, 196);
			if (State) {
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

		case CAT:
			glColor3ub(28, 198, 56);
			if (State) {
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

		case WATER_BALLOON:
			glColor3ub(67, 33, 193);
			if (State) {
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

		case DEFAULT:
			glColor3ub(255,0,0);
			if (State) {
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

double Bullet::GetRadius(void)
{
	return Radius;
}

void Bullet::ChangeLife (void){
	Life -= 1;
	if( Life <= 0){
		State = false;
	}
}

void Bullet::SetLife( int level ){
	LifeInitValue = (int)1.5*level;
}

bool Bullet::GetState(void){
	return State;
}

int Bullet::GetLife(void){
    return Life;
}

void Bullet::CheckScreen(void){
	if (Position.x < 0 || 800 < Position.x ||
		Position.y < 0 || 600 < Position.y){
		
		State = false;
	}
}

void Bullet::ChangeSpeed(int Delta){
	
	if( 0 < Delta || 50 < InitSpeed ){
		InitSpeed += Delta;
	}
}

void Bullet::Shoot (bool IsS){
	IsShoot = IsS;
	Life = LifeInitValue;
}

bool Bullet::GetIsShoot(void){
	return IsShoot;
}

