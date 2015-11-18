#include "SupIntroFlash.hpp"

class Flash{
public:
    int gameCharge;
    int money;
    FlashCard card[144];
    TextString text[144];
    
    Flash();
    Flash(int money_from, int gameCharge_from);
    ~Flash();
    void Set(int money_from, int gameCharge_from);
    void GenerateCard();
    void Display();
    void Add();
};




