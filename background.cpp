#include "Game.h"


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
    
    //glShadeModel(GL_SMOOTH);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
    glBegin(GL_QUADS);
    glColor3ub(200,30,30);
    glVertex2i(x,y);
    
    //glColor3ub(200,30,30);
    glVertex2i(x+50,y);
    
    //glColor3ub(0,0,0);
    glVertex2i(x+50,y-50);
    
    //glColor3ub(0,0,0);
    glVertex2i(x,y-50);
    
    glEnd();
    
   // glDisable(GL_BLEND);

}
MountainCube::MountainCube()
{
    x=0;
    y=0;
    state=1;
    
}

void Background::ReadFile()
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

void Background::cleanup()
{
    if (nullptr!=CubePtr)
    {
        delete [] CubePtr;
        CubePtr=nullptr;
    }
}


void Background::Initial()
{
    ReadBackground();
    ReadFile();
}

void Background::Run(Weapon &gun)
{
//    checkcollision(gun);
    DrawBackground();
    DrawMountain();
}

Background::Background()
{
	boundaryX1=200;
    boundaryX2=600;
    CubePtr=nullptr;
}

Background::~Background()
{
    cleanup();
}

void Background::DrawBackground()
{
    glRasterPos2d(0,decoder.hei-1);
    glDrawPixels(decoder.wid,decoder.hei,GL_RGBA,GL_UNSIGNED_BYTE,decoder.rgba);
}

void Background::ReadBackground()
{
    decoder.Decode("background.png");
    decoder.Flip();
}

double Background::GetBoundaryX1()
{
    return boundaryX1;
}

double Background::GetBoundaryX2()
{
    return boundaryX2;
}


void Background::DrawMountain(void)
{
    for (int i=0;i<nCube;i++)
    {
        if (CubePtr[i].state==1)
        {
            CubePtr[i].draw();
            printf("%f  %f\n", CubePtr[i].GetX(),CubePtr[i].GetY());
        }
    }
}

void Background::checkcollision(Weapon &gun)
{
    for (int i=0;i<nCube;i++)
    {
        if (gun.GetBullet()->x()>CubePtr[i].GetX()
            && gun.GetBullet()->x()< CubePtr[i].GetX()+w
            && gun.GetBullet()->y()<CubePtr[i].GetY()
            && gun.GetBullet()->y()>CubePtr[i].GetY()-h
            && CubePtr[i].state==1
            && gun.GetBullet()->GetLife()>0)
        {
            CubePtr[i].state=0;
            gun.GetBullet()->ChangeLife();

        }
    }
}


