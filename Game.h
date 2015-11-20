#include "Obstacle.h"
#include "Weapons.h"
#include "player.h"
#include "character.h"
class Game
{
public:
    Background bacground;
    Obstacle obstacle1;
    Obstacle obstacle2;
    Weapon weapon;
    Bullet bullet
    Player player;
    Character character;
    void Initial(void);
    void Run(void);
};


