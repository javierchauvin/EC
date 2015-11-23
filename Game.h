#include "Obstacle.h"
#include "Weapons.h"
#include "player.h"
#include "character.h"
#include "background.h"
class Game
{
public:
    background background;
    Obstacle obstacle1;
    Obstacle obstacle2;
    Weapon weapon;
    Bullet bullet;
    Player player;
    Character character;
    void Initial(void);
    void Run();
};


