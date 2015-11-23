#include "background.h"


int Parse(int wordTop[],int wordLength[],int maxNumWord,char str[])
{
    int state=0;  // 0:Blank   1:Visible Letter
    int nw=0;
    for(int i=0; 0!=str[i]; ++i)
    {
        switch(state)
        {
            case 0:
                if(' '!=str[i] && isprint(str[i]))
                {
                    if(nw<maxNumWord)
                    {
                        wordTop[nw]=i;
                        wordLength[nw]=1;
                    }
                    else
                    {
                        goto LOOPOUT;
                    }
                    ++nw;
                    state=1;
                }
                else
                {
                }
                break;
            case 1:
                if(' '!=str[i] && isprint(str[i]))
                {
                    wordLength[nw-1]++;
                }
                else
                {
                    state=0;
                }
                break;
        }
    }
LOOPOUT:
    
    return nw;
}


double MountainCube::GetX()
{
    return x;
}

double MountainCube::GetY()
{
    return y;
}


void MountainCube::MakeFromString(char str[])
{
    int wordTop[2],wordLength[2],nWord;
    nWord=Parse(wordTop,wordLength,2,str);
    
    if(2<=nWord)
    {
        x=atoi(str+wordTop[0]);
        y=atoi(str+wordTop[1]);
    }
}

void MountainCube::draw()
{
    
    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
    glBegin(GL_QUADS);
    glColor3ub(200,30,30);
    glVertex2i(x,y);
    
    glColor3ub(200,30,30);
    glVertex2i(x+50,y);
    
    glColor3ub(0,0,0);
    glVertex2i(x+50,y-50);
    
    glColor3ub(0,0,0);
    glVertex2i(x,y-50);
    
    glEnd();
    
    glDisable(GL_BLEND);

}
MountainCube::MountainCube()
{
    x=0;
    y=0;
    state=1;
}

void background::ReadFile()
{
    cleanup();
    
    FILE *fp=fopen("background.txt","r");
    if(nullptr!=fp)
    {
        char str[256];
        if(nullptr!=fgets(str,255,fp))
        {
            nCube=atoi(str);
            CubePtr =new MountainCube [nCube];
            for(int i=0; i<nCube && nullptr!=fgets(str,255,fp); ++i)
            {
                CubePtr[i].MakeFromString(str);
            }
        }
        
        fclose(fp);
    }
}

void background::cleanup()
{
    if (nullptr!=CubePtr)
    {
        delete [] CubePtr;
        CubePtr=nullptr;
    }
}


void background::Initial()
{
    CubePtr=nullptr;
    ReadBackground();
    ReadFile();
}

void background::Run(weapon* gun)
{
    checkcollision(gun);
    DrawBackground();
    DrawMountain();
}

background::background()
{

}

background::~background()
{
    cleanup();
}

void background::DrawBackground()
{
    glRasterPos2d(0,decoder.hei-1);
    glDrawPixels(decoder.wid,decoder.hei,GL_RGBA,GL_UNSIGNED_BYTE,decoder.rgba);
}

void background::ReadBackground()
{
    decoder.Decode("background.png");
    decoder.Flip();
}

double background::GetBoundaryX1()
{
    return boundaryX1;
}

double background::GetBoundaryX2()
{
    return boundaryX2;
}


void background::DrawMountain(void)
{
    for (int i=0;i<nCube;i++)
    {
        if (CubePtr[i].state==1)
        {
            CubePtr[i].draw();
        }
    }
}

void background::checkcollision(weapon* gun)
{
    for (int i=0;i<nCube;i++)
    {
        if (gun.Bulls.x()>CubePtr[i].GetX() && gun.Bulls.x()< CubePtr[i].GetX()+w && gun.Bulls.y()<CubePtr[i].GetY() && gun.Bulls.y()>CubePtr[i].GetY()-h && CubePtr[i].state==1 && gun.Bulls.GetLife>0)
        {
            CubePtr[i].state=0;
            gun.Bulls.ChangeLife();

        }
    }
}


