#include "Flash.hpp"
Flash::Flash(){
    gameCharge = 0;
    money = 0;
    GenerateCard();
}
Flash::Flash(int money_from, int gameCharge_from){
    money = money_from;
    gameCharge = gameCharge_from;
    GenerateCard();
}
Flash::~Flash(){
    gameCharge = 0;
    money = 0;
    for(int i=0; i<144; ++i){
        card[i].a = 0;
        card[i].b = 0;
        text[i] = 0;
    }
}
void Flash::Set(int money_from, int gameCharge_from){
    money = money_from;
    gameCharge = gameCharge_from;
}
void Flash::GenerateCard(){
    srand(time(NULL));
    for(int i=0; i<144; ++i){
        card[i].a=i;
        card[i].b=i;
    }
    Shuffle(144,card);
    for(int i=0; i<144; ++i){
        card[i].a=1+(card[i].a%12);
        card[i].b=1+(card[i].b/12);
        if(card[i].a<10){
            text[i].Add(48+card[i].a);
            text[i].Add(' ');
            text[i].Add('x');
            text[i].Add(' ');
        }
        else{
            text[i].Add(48+card[i].a/10);
            text[i].Add(48+card[i].a%10);
            text[i].Add(' ');
            text[i].Add('x');
            text[i].Add(' ');
        }
        if(card[i].b<10){
            text[i].Add(48+card[i].b);
            text[i].Add(' ');
            text[i].Add('=');
            text[i].Add(' ');
        }
        else{
            text[i].Add(48+card[i].b/10);
            text[i].Add(48+card[i].b%10);
            text[i].Add(' ');
            text[i].Add('=');
            text[i].Add(' ');
        }
    }
}

void Flash::Display(){
    int ans;
    int terminate = 1;
    int j = 0, state = 0;
    char temp[10];
    char money_dis[100], gc_dis[100];
    
    FsOpenWindow(16,16,800,600,1);
    TextInput t;
    
    while(terminate == 1){
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        strcpy( money_dis, "Your Money: ");
        strcpy( gc_dis, "Your Game Charge: ");
        
        ans=card[j].a*card[j].b; // record answer
        t.SetCaption(text[j].GetPointer());
        t.SetDefaultText("");
        terminate = t.FlashInput(); // input test: if FSKEY_END, terminate becomes 0
        if(0!=terminate){
            if(ans==atoi(t.GetString())){
                state = 1; // "state" for prolong fssleep
                glColor3ub(255,255,153);
                glRasterPos2d(150,300);
                YsGlDrawFontBitmap20x32("Correct!");
                money ++;
                gameCharge ++;
                sprintf(temp, "%d", money);
                strncat(money_dis, temp, 12);
                sprintf(temp, "%d", gameCharge);
                strncat(gc_dis, temp, 18);
                glColor3ub(230,230,230);
                glRasterPos2d(150,350);
                YsGlDrawFontBitmap20x32(money_dis);
                glColor3ub(230,230,230);
                glRasterPos2d(150,400);
                YsGlDrawFontBitmap20x32(gc_dis);
            }
            else{
                state = 1; // "state" for prolong fssleep
                glColor3ub(255,153,153);
                glRasterPos2d(150,300);
                YsGlDrawFontBitmap20x32("Wrong!");
                sprintf(temp, "%d", money);
                strncat(money_dis, temp, 12);
                sprintf(temp, "%d", gameCharge);
                strncat(gc_dis, temp, 18);
                glColor3ub(230,230,230);
                glRasterPos2d(150,350);
                YsGlDrawFontBitmap20x32(money_dis);
                glColor3ub(230,230,230);
                glRasterPos2d(150,400);
                YsGlDrawFontBitmap20x32(gc_dis);
            }
        }
        j++;
        FsSwapBuffers();
        if (state == 1){ // prolong fssleep
            FsSleep(1200);
            state = 0;
        }
        FsSleep(0);
    }
}

void Flash::Add(){
    money ++;
    gameCharge ++;
}

