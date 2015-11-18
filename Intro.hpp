#include "SupIntroFlash.hpp"

template <int number>
class UserIntro{
protected:
    TextString user;
    
public:
    UserIntro();
    ~UserIntro();
    void Set(const char from[]);
    void Run();
    TextString GetUser();
};

// ======================

class UserIntro1: public UserIntro<1>{
};
class UserIntro2: public UserIntro<2>{
};

// ======================

void Intro(TextString * UserName1, TextString * UserName2);
