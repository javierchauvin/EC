#ifndef Shop_hpp
#define Shop_hpp

#include <math.h>
#include "fssimplewindow.h"
#include <stdio.h>
#include "yspng.h"
#include "ysglfontdata.h"
#include <string.h>
#include "Game.h"

class WeaponText{
public:
    char name[10];
    double x, y;
    double xl,yl,xh,yh;
    
    WeaponText();
    void Set(double length, double xOut, double yOut, char WeaponName[]);
};

class Shop{
public:
    WeaponText w1, w2, w3, w4, w5, w6, exit;
    char HaveWeaponStr[50], BuyWeaponStr[50], NoMoneyStr[50];
    int w1Check, w2Check, w3Check, w4Check, w5Check, w6Check;
    
    Shop();
    void AssignWeaponCheck(Player player); // add "Player player" as input
    void AssignToPlayer(Player &player); // add "Player player" as input
    void Run(Player &player, int &status);
    void DrawHaveWeaponStr();
    void DrawBuyWeaponStr();
    void DrawNoMoneyStr();
    void DrawMoney(int money);
    void DrawWeaponList();
};

int  DrawShopWeapon(WeaponText w);
void ShopBackGround();

#endif /* Shop_hpp */
