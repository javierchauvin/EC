#include "Shop.hpp"

WeaponText::WeaponText(){
    x = 0;
    y = 0;
    xl = 0;
    yl = 0;
    xh = 0;
    yh = 0;
    for (int i = 0; i < 10; i++){
        name[i] = 0;
    }
}

void WeaponText::Set(double length, double xOut, double yOut, char WeaponName[]){
    for (int i = 0; i < strlen(WeaponName); i++){
        name[i] = WeaponName[i];
    }
    x = xOut;
    y = yOut;
    xl = x-10;
    yl = y-30;
    xh = x+length;
    yh = y+10;
}

// ===================

Shop::Shop(){
    char str[] = "You already have this weapon with highest level!";
    char str2[] = "You successfully buy/upgrade this weapon!";
    char str3[] = "You have not enough money";
    w1Check = 0;
    w2Check = 0;
    w3Check = 0;
    w4Check = 0;
    w5Check = 0;
    w6Check = 0;
    char w1Char[] = "weapon1";
    char w2Char[] = "weapon2";
    char w3Char[] = "weapon3";
    char w4Char[] = "weapon4";
    char w5Char[] = "weapon5";
    char w6Char[] = "weapon6";
    w1.Set(150, 180, 105, w1Char);
    w2.Set(150, 480, 105, w2Char);
    w3.Set(150, 180, 265, w3Char);
    w4.Set(150, 480, 265, w4Char);
    w5.Set(150, 180, 410, w5Char);
    w6.Set(150, 480, 410, w6Char);
    for (int i = 0; i < strlen(str); i++){
        HaveWeaponStr[i] = str[i];
    }
    for (int i = 0; i < strlen(str2); i++){
        BuyWeaponStr[i] = str2[i];
    }
    for (int i = 0; i < strlen(str2); i++){
        NoMoneyStr[i] = str3[i];
    }
}

// assign player weapon list to w?Check
void Shop::AssignWeaponCheck(Player player){
    int * WeaponList;
    WeaponList = player.getWeaponList();
    w1Check = WeaponList[0];
    w2Check = WeaponList[1];
    w3Check = WeaponList[2];
    w4Check = WeaponList[3];
    w5Check = WeaponList[4];
    w6Check = WeaponList[5];
};

// Draw HaveWeaponStr
void Shop::DrawHaveWeaponStr(){
    glColor3d(1,0,0);
    glRasterPos2d(20, 550);
    YsGlDrawFontBitmap16x20(HaveWeaponStr);
}

// Draw BuyWeaponStr
void Shop::DrawBuyWeaponStr(){
    glColor3d(0,0,0);
    glRasterPos2d(80, 550);
    YsGlDrawFontBitmap16x20(BuyWeaponStr);
}

// Draw NoMoneyStr
void Shop::DrawNoMoneyStr(){
    glColor3d(0,0,0);
    glRasterPos2d(180, 550);
    YsGlDrawFontBitmap16x20(NoMoneyStr);
}

// Draw money
void Shop::DrawMoney(int money){
    char moneyDisplay[10] = "$", temp[10];
    sprintf(temp, "%d", money);
    strncat(moneyDisplay, temp, 10);
    
    glColor3d(0,0,0);
    glRasterPos2d(35, 60);
    YsGlDrawFontBitmap20x28(moneyDisplay);
}

// Draw weaponlist
void Shop::DrawWeaponList(){
    char w1[20] = "weapon1: ";
    char w2[20] = "weapon2: ";
    char w3[20] = "weapon3: ";
    char w4[20] = "weapon4: ";
    char w5[20] = "weapon5: ";
    char w6[20] = "weapon6: ";
    char temp[10];
    sprintf(temp, "%d", w1Check);
    strncat(w1, temp, 10);
    sprintf(temp, "%d", w2Check);
    strncat(w2, temp, 10);
    sprintf(temp, "%d", w3Check);
    strncat(w3, temp, 10);
    sprintf(temp, "%d", w4Check);
    strncat(w4, temp, 10);
    sprintf(temp, "%d", w5Check);
    strncat(w5, temp, 10);
    sprintf(temp, "%d", w6Check);
    strncat(w6, temp, 10);
    
    glColor3d(0,0,0);
    glRasterPos2d(30, 100);
    YsGlDrawFontBitmap10x14(w1);
    glRasterPos2d(30, 130);
    YsGlDrawFontBitmap10x14(w2);
    glRasterPos2d(30, 160);
    YsGlDrawFontBitmap10x14(w3);
    glRasterPos2d(30, 190);
    YsGlDrawFontBitmap10x14(w4);
    glRasterPos2d(30, 220);
    YsGlDrawFontBitmap10x14(w5);
    glRasterPos2d(30, 250);
    YsGlDrawFontBitmap10x14(w6);
}

// assign shopping result to Player
void Shop::AssignToPlayer(Player &player){
    player.setWeaponList(0, w1Check);
    player.setWeaponList(1, w2Check);
    player.setWeaponList(2, w3Check);
    player.setWeaponList(3, w4Check);
    player.setWeaponList(4, w5Check);
    player.setWeaponList(5, w6Check);
};

void Shop::Run(Player &player, int &status){
    int w1Temp, w2Temp, w3Temp, w4Temp, w5Temp, w6Temp;
    int state = 0; // determine whether to FsSleep
    int money = player.getMoney();
    int minMoney = 5;
    
    while (FSKEY_ESC!=FsInkey()) {
        FsPollDevice();
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
 
        ShopBackGround();
        DrawMoney(money);
        DrawWeaponList();
        
        w1Temp = DrawShopWeapon(w1);
        w2Temp = DrawShopWeapon(w2);
        w3Temp = DrawShopWeapon(w3);
        w4Temp = DrawShopWeapon(w4);
        w5Temp = DrawShopWeapon(w5);
        w6Temp = DrawShopWeapon(w6);
        
        if (w1Temp == 1){
            state = 1;
            if( w1Check > 4){ DrawHaveWeaponStr();}
            else if (money < minMoney){ // not enough money
                DrawNoMoneyStr();
            }
            else {
                w1Check ++;
                DrawBuyWeaponStr();
                money -= 5;
            }
        }
        if (w2Temp == 1){
            state = 1;
            if( w2Check > 4){ DrawHaveWeaponStr(); }
            else if (money < minMoney){
                DrawNoMoneyStr();
            }
            else {
                w2Check ++;
                DrawBuyWeaponStr();
                money -= 5;
            }
        }
        if (w3Temp == 1){
            state = 1;
            if( w3Check > 4){ DrawHaveWeaponStr(); }
            else if (money < minMoney){
                DrawNoMoneyStr();
            }
            else {
                w3Check ++;
                DrawBuyWeaponStr();
                money -= 5;
            }
        }
        if (w4Temp == 1){
            state = 1;
            if( w4Check > 4){ DrawHaveWeaponStr();}
            else if (money < minMoney){
                DrawNoMoneyStr();
            }
            else {
                w4Check ++;
                DrawBuyWeaponStr();
                money -= 5;
            }
        }
        if (w5Temp == 1){
            state = 1;
            if( w5Check > 4){ DrawHaveWeaponStr();}
            else if (money < minMoney){
                DrawNoMoneyStr();
            }
            else {
                w5Check ++;
                DrawBuyWeaponStr();
                money -= 5;
            }
        }
        if (w6Temp == 1){
            state = 1;
            if( w6Check > 4){
                DrawHaveWeaponStr();
            }
            else if (money < minMoney){
                DrawNoMoneyStr();
            }
            else {
                w6Check ++;
                DrawBuyWeaponStr();
                money -= 5;
            }
        }

        FsSwapBuffers();
        if (state == 1){ // prolong fssleep
            FsSleep(1000);
            state = 0;
        }
        FsSleep(50);
    }
    player.setMoney(money);
    AssignToPlayer(player);
    status = 1;
}


// ===================

int  DrawShopWeapon(WeaponText w)
{
    int lb,mb,rb,mxm,mym;
    FsGetMouseEvent(lb,mb,rb,mxm,mym);
    glColor3d(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex2d(w.xl, w.yl);
    glVertex2d(w.xl, w.yh);
    glVertex2d(w.xh, w.yh);
    glVertex2d(w.xh, w.yl);
    glEnd();
    
    glColor3d(0,0,0);
    glRasterPos2d(w.x,w.y);
    YsGlDrawFontBitmap20x28(w.name);
    
    if((mxm<=w.xh)&&(mxm>=w.xl)&&(mym>=w.yl)&&(mym<=w.yh)&&(lb==1))
    {
        return 1;
    }
    return 0;
}


void ShopBackGround()
{
    YsRawPngDecoder decoder;
    decoder.Decode("shop.png");
    decoder.Flip();
    glRasterPos2d(0,decoder.hei-1);
    glDrawPixels(decoder.wid,decoder.hei,GL_RGBA,GL_UNSIGNED_BYTE,decoder.rgba);
}

