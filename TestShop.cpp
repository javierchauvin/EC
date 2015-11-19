#include "Shop.hpp"

int main(){
    int money = 100;
    Shop shop;
    shop.AssignWeaponCheck(); // Assign weapon list from player to shop
    
    FsOpenWindow(16, 16, 800, 600, 1);
    shop.Run(money); // should input money
    
    return 0;
}