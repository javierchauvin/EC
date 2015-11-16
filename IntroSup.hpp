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
void BackGround()
{
    YsRawPngDecoder decoder;
    decoder.Decode("blackboard_final.png");
    decoder.Flip();
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glRasterPos2d(0,decoder.hei-1);
    glDrawPixels(decoder.wid,decoder.hei,GL_RGBA,GL_UNSIGNED_BYTE,decoder.rgba);
}

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

TextString::TextString() : str(NULL)
{
}

TextString::TextString(const char from[]) : str(NULL)
{
    Set(from);
}

TextString::TextString(const TextString &from) : str(NULL)
{
    Set(from.GetPointer());
}

TextString::~TextString()
{
    CleanUp();
}

void TextString::CleanUp()
{
    if(NULL!=str)
    {
        delete [] str;
        str=NULL;
    }
}

void TextString::Set(const char from[])
{
    if(NULL!=from)
    {
        CleanUp();
        
        const int n=strlen(from);
        str=new char [n+1];
        if(NULL!=str)
        {
            strcpy(str,from);
        }
    }
}

void TextString::Add(const char from[])
{
    if(NULL!=from)
    {
        const int nCurrent=Strlen();
        const int nFrom=strlen(from);
        
        char *newStr=new char [nCurrent+nFrom+1];
        if(NULL!=newStr)
        {
            strcpy(newStr,GetPointer());
            strcpy(newStr+nCurrent,from);
            if(NULL!=str)
            {
                delete [] str;
            }
            str=newStr;
        }
    }
}

void TextString::Add(const char c)
{
    const int nCurrent=Strlen();
    
    char *newStr=new char [nCurrent+2];
    if(NULL!=newStr)
    {
        strcpy(newStr,GetPointer());
        newStr[nCurrent]=c;
        newStr[nCurrent+1]=0;
        if(NULL!=str)
        {
            delete [] str;
        }
        str=newStr;
    }
}

void TextString::BackSpace(void)
{
    if(NULL!=str)
    {
        int n=Strlen();
        if(0<n)
        {
            str[n-1]=0;
        }
    }
}

void TextString::DeleteLastControlCode(void)
{
    int n;
    for(n=strlen(str)-1; 0<=n; n--)
    {
        if(0!=isprint(str[n]))
        {
            break;
        }
        str[n]=0;
    }
}

const char *TextString::Fgets(FILE *fp)
{
    if(NULL!=fp)
    {
        CleanUp();
        
        int firstLine=1;
        const int nBuf=8;
        char buf[nBuf+1];
        
        buf[nBuf]=0;
        for(;;)
        {
            if(NULL==fgets(buf,nBuf,fp))
            {
                if(0!=firstLine)
                {
                    return NULL;
                }
                else
                {
                    break;
                }
            }
            else
            {
                firstLine=0;
                Add(buf);
                
                int nChar=strlen(buf);
                if(buf[nChar-1]=='\n' || buf[nChar-1]=='\a')
                {
                    break;
                }
            }
        }
        
        DeleteLastControlCode();
        return str;
    }
    return NULL;
}
const char *TextString::GetPointer(void) const
{
    if(NULL!=str)
    {
        return str;
    }
    else
    {
        return "";
    }
}

const int TextString::Strlen(void) const
{
    return strlen(GetPointer());
}

void TextString::Print(void) const
{
    if(NULL!=str)
    {
        printf("%s\n",str);
    }
}

const TextString &TextString::operator=(const TextString &from)
{
    Set(from.GetPointer());
    return *this;
}

// ======================

class TextInput{
protected:
    TextString caption;
    TextString str;
public:
    void SetCaption(const char newCaption[]);
    void SetDefaultText(const char defTxt[]);
    const char *GetString(void) const;
    int Input(void);
    void Draw(void);
};

void TextInput::SetCaption(const char newCaption[]){
    caption.Set(newCaption);
}

void TextInput::SetDefaultText(const char defTxt[]){
    str.Set(defTxt);
}

const char *TextInput::GetString(void) const{
    return str.GetPointer();
}

void TextInput::Draw(void){
    BackGround();
    glColor3ub(230,230,230);
    glRasterPos2d(150,150);
    YsGlDrawFontBitmap20x32(caption.GetPointer());
    glColor3ub(230,230,230);
    glRasterPos2d(150,225);
    YsGlDrawFontBitmap20x32(str.GetPointer());
    switch(time(NULL)%2)
    {
//        case 0:
//            YsGlDrawFontBitmap20x32("_");
//            break;
        case 1:
            YsGlDrawFontBitmap20x32("|");
            break;
    }
}

int TextInput::Input(void){
    FsPollDevice();
    while(FSKEY_NULL!=FsInkey() || 0!=FsInkeyChar())
    {
        FsPollDevice();
    }
    
    for(;;)
    {
        FsPollDevice();
        
        int key=FsInkey();
        
        switch(key)
        {
            case FSKEY_ESC:
                return 0;
            case FSKEY_ENTER:
                return 1;
            case FSKEY_BS:
                str.BackSpace();
                break;
        }
        
        const char c=FsInkeyChar();
        if(0!=c && 0!=isprint(c))
        {
            str.Add(c);
        }
        
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        Draw();
        FsSwapBuffers();
        
        FsSleep(20);
    }
    return 0;
}

// ===================

class FlashCard
{
public:
    int a,b;

};


void SwapFlashCard(FlashCard &F1,FlashCard &F2)
{
    FlashCard C;
    C = F1;
    F1 = F2;
    F2 = C;
}

// ==================

void Shuffle(int nCard,FlashCard card[])
{
    for(int i=0; i<nCard; ++i)
    {
        int idx=rand()%nCard;
        SwapFlashCard(card[i],card[idx]);
    }
}
