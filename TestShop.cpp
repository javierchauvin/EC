#include "Shop.hpp"

int main(){
    int status = 0;
    Player player1;
    player1.setMoney(100);
    Shop shop;
    shop.AssignWeaponCheck(player1); // Assign weapon list from player to shop
    
    FsOpenWindow(16, 16, 800, 600, 1);
    shop.Run(player1, status); // should input money
    
    return 0;
}