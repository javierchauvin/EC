#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "fssimplewindow.h"
#include "player.h"
#include "character.h"

#define TYPESOFWEAPONS 3
#define TANK 0
#define UNICORN 1
#define EINSTEIN 2

//weaponList[weapon#] = weapon level

/* Constructor1 */
Player::Player(){
    X = 0;
    Y = 0;
    money = 0;
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
}
void Player::playerSet(int initX, int initY){
    X = initX;
    Y = initY;
}
void Player::movePlayer(int key){
    switch(key)
    {
        case FSKEY_LEFT:
            X = X - 5;
            break;
        case FSKEY_RIGHT:
            X = X + 5;
            break;
    }
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

/* getWeaponList - Call this function to get weapon list */
int* Player::getWeaponList(){
    return weaponList;
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
    a->drawCharacter(X, Y);
}
int Player::getX(){
    return X;
}
int Player::getY(){
    return Y;
}

int Parse(int wordTop[],int wordLength[],int maxNumWord,char str[])
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
void Player::ReadProperties()
{
    printf("Enter file name> "); //this will be replaced by Santo's menu
    char userfile[50];
    fgets(userfile, 50, stdin);
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
			nWord=Parse(wordTop,wordLength,10,str);
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

