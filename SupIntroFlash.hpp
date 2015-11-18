#ifndef B_H
#define B_H

#include <stdio.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include <stdlib.h>
#include <time.h>
#include "yspng.h"
#include "yspngenc.h"
#include <string.h>
#include <string>
#include <ctype.h>
using namespace std;

// ==================

void BackGroundIntro();
void BackGroundFlash();

// ==================

class TextString
{
protected:
    char *str;
    
public:
    TextString();
    TextString(const char from[]);
    TextString(const TextString &str);
    ~TextString();
    void CleanUp();
    void Set(const char from[]);
    void Add(const char from[]);
    void Add(const char c);
    void BackSpace(void);
    const char *Fgets(FILE *fp);
    void DeleteLastControlCode(void);
    const char *GetPointer(void) const;
    const int Strlen(void) const;
    void Print(void) const;
    const TextString &operator=(const TextString &from);
};

// ======================

class TextInput{
protected:
    TextString caption;
    TextString str;
public:
    void SetCaption(const char newCaption[]);
    void SetDefaultText(const char defTxt[]);
    const char *GetString(void) const;
    int IntroInput(void);
    int FlashInput(void);
    void DrawIntro(void);
    void DrawFlash(void);
};

// ===================

class FlashCard
{
public:
    int a,b;

};

// ==================

void SwapFlashCard(FlashCard &F1,FlashCard &F2);
void Shuffle(int nCard,FlashCard card[]);
#endif