#ifndef PLAYER_CLASS_H_IS_INCLUDED
#define PLAYER_CLASS_H_IS_INCLUDED

#define TYPESOFWEAPONS 6

class Player{
private:
    int X, Y, direction;
    int money;
    /* weaponList[weapon#] = level 
     * level 0 means player doesn't own that weapon yet */
    int weaponList[TYPESOFWEAPONS];
    int myCharacter;
    char userfile[50];
public:
    Player();
    Player(int initX, int initY);
    ~Player();
    void playerSet(int initX, int initY);
    void movePlayer();
    void drawPlayer();
    int getX();
    int getY();
    int getDirection();
    void ReadProperties(char *username);
    void SaveProperties();
    void setMyCharacter(int character);
    int getMyCharacter();
    int *getWeaponList();
    void setWeaponList(int index, int level);
    int getMoney();
    void setMoney(int newMoney);
    void Initial();
    void Run();
};

#endif