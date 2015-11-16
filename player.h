#ifndef PLAYER_CLASS_H_IS_INCLUDED
#define PLAYER_CLASS_H_IS_INCLUDED

#define TYPESOFWEAPONS 3

class Player{
private:
    int X, Y;
    int money;
    int weaponList[TYPESOFWEAPONS];
    int myCharacter;
public:
    Player();
    Player(int initX, int initY);
    ~Player();
    void playerSet(int initX, int initY);
    void movePlayer(int key);
    void drawPlayer();
    int getX();
    int getY();
    void ReadProperties();
    void setMyCharacter(int character);
    int getMyCharacter();
    int *getWeaponList();
    int getMoney();
};

#endif