#include "Obstacle.h"
#include "Weapons.h"
#include "player.h"
#include "character.h"
class Game
{
public:
    Background bacground;
    Obstacle obstacle;
    Weapon weapon;
    Bullet bullet
    Player player;
    Character character;
    void Initial(void);
    void Run(void);
};


