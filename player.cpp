
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "fssimplewindow.h"
#include "Game.h"

#define TYPESOFWEAPONS 6
#define TANK 0
#define UNICORN 1
#define EINSTEIN 2

//weaponList[weapon#] = weapon level

/* Constructor1 */
Player::Player(){
    X = 0;
    Y = 0;
    money = 0;
    direction = 0;
    myCharacter = TANK; //default character
    for (int i = 0; i < TYPESOFWEAPONS; i++) {
        weaponList[i] = 0; //default level is 0
    }
}
/* Constructor2 */
Player::Player(int initX, int initY){
    X = initX;
    Y = initY;
}
/* Destructor */
Player::~Player(){
    X = 0;
    Y = 0;
    direction = 0;
    myCharacter = TANK;
}
void Player::playerSet(int initX, int initY){
    X = initX;
    Y = initY;
}

void Player::Initial(){
    X = 0;
    Y = 0;
    direction = 0; /* 0: face right, 1: face left */
    myCharacter = TANK;
}

void Player::Run(){
    drawPlayer();
    movePlayer();
    
}

void Player::movePlayer(){
    //FsPollDevice();
    int key = FsInkey();
    //glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    Background bg;
    int boundary1 = bg.GetBoundaryX1();
    int boundary2 = bg.GetBoundaryX2();
    
    switch(key)
    {
        case FSKEY_LEFT:
            if (X < 400) {
                if (X > 5) { /* player 1 */
                    X -= 5;
                }
            }
            if (X > 400) {
                if (X > 400) { /* player 2 */
                    if (X > boundary2 + 5) {
                        X -= 5;
                    }
                }
            }
            break;
        case FSKEY_RIGHT:
            if (X < 400) { /* player 1 */
                if (X < boundary1 - 5) {
                    X += 5;
                }
            }
            if (X > 400) { /* player 1 */
                if (X < 795) {
                    X += 5;
                }
            }
            break;
    }
    //FsSwapBuffers();
    //FsSleep(25);
}

int Player::getX(){
    return X;
}
int Player::getY(){
    return Y;
}
int Player::getDirection(){
    return direction;
}
/*
 * setMyCharacter - Menu calls this function after user
 * chooses his/her character
 */
void Player::setMyCharacter(int character){
    myCharacter = character;
}

/*
 * getMyCharacter - Call this function to get user's current character
 */
int Player::getMyCharacter(){
    return myCharacter;
}

/* getMoney - Call this function to get user's money */
int Player::getMoney(){
    return money;
}

/* setMoney - Call this function to set user's money to newmoney*/
void Player::setMoney(int newmoney){
    money = newmoney;
}

/* getWeaponList - Call this function to get weapon list */
int* Player::getWeaponList(){
    return weaponList;
}

/* setWeaponList - Call this function to set weapon list */
void Player::setWeaponList(int index, int level){
    weaponList[index] = level;
}

/*
 * drawPlayer - draws player's character
 */
void Player::drawPlayer(){
    Character *a;
    switch (myCharacter){
        case TANK:
            a = new Tank();
            break;
        case UNICORN:
            a = new Unicorn();
            break;
        case EINSTEIN:
            a = new Einstein();
            break;
        default:
            a = new Tank();
            break;
    }
    a->drawCharacter(X, Y, direction);
}


int Parse1(int wordTop[],int wordLength[],int maxNumWord,char str[])
{
	int state=0;  // 0:Blank   1:Visible Letter
	int nw=0;
	for(int i=0; 0!=str[i]; ++i)
	{
		switch(state)
		{
		case 0:
			if(' '!=str[i] && isprint(str[i]))
			{
				if(nw<maxNumWord)
				{
					wordTop[nw]=i;
					wordLength[nw]=1;
				}
				else
				{
					goto LOOPOUT;
				}
				++nw;
				state=1;
			}
			else
			{
			}
			break;
		case 1:
			if(' '!=str[i] && isprint(str[i]))
			{
				wordLength[nw-1]++;
			}
			else
			{
				state=0;
			}
			break;
		}
	}
LOOPOUT:

	return nw;
}

void GetWord(char wd[],char str[],int wordTop,int wordLength,int bufSize)
{
	int l=wordLength;
	if(bufSize<l)
	{
		l=bufSize;
	}
	strncpy(wd,str+wordTop,l);
	wd[l]=0;
}

/*
 * ReadProperties - Reads from .txt file specified by user
 * and saves money in money and weapon levels in weaponList
 *
 */
void Player::ReadProperties(char *username)
{
    strncpy(userfile, username, 50);
    //take off control code
    if (userfile[strlen(userfile) - 1] == '\n')
    {
        userfile[strlen(userfile) - 1] = '\0';
    }
    strcat(userfile,".txt");
    FILE *fp = fopen(userfile,"r");

	if (nullptr!=fp)
    {
		char str[256];
        money = atoi(fgets(str,255,fp));
        printf("money = %d\n", money);
		while(nullptr!=fgets(str,255,fp))
		{
			int nWord=0;
			int wordTop[10],wordLength[10];
			nWord=Parse1(wordTop,wordLength,10,str);
            char wstr[256], wlevelstr[256];
            GetWord(wstr,str,wordTop[0],wordLength[0],255);
            GetWord(wlevelstr,str,wordTop[1],wordLength[1],255);
            int w = atoi(wstr);
            int wlevel = atoi(wlevelstr);
            
            switch (w) {
                case 0:
                    printf("Weapon 0 is at level %d\n", wlevel+1);
                    weaponList[0] = wlevel;
                    break;
                case 1:
                    printf("Weapon 1 is at level %d\n", wlevel+1);
                    weaponList[1] = wlevel;
                    break;
                case 2:
                    printf("Weapon 2 is at level %d\n", wlevel+1);
                    weaponList[2] = wlevel;
                    break;
                default:
                    break;
            }
            
		}

		fclose(fp);
	}
	else
	{
		printf("Error! Could not open file.\n");
        exit(EXIT_FAILURE);
	}
}

void Player::SaveProperties(){
    FILE *fp = fopen(userfile,"w");
    
    if(fp==NULL)
    {
        printf("Error! Could not open file.\n");
        exit(EXIT_FAILURE);
    }
    
    fprintf(fp,"%d\n", money);
    for (int i = 0; i < 6; i++) {
        fprintf(fp,"%d %d\n", i, weaponList[i]);
    }
    fclose(fp);
    
}
