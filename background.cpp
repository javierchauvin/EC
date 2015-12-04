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
    
    


    
    glBegin(GL_QUADS);
    glColor3ub(0,100,100);

    glVertex2i(x,y);
    
    glColor3ub(0,100,100);
    glVertex2i(x+50,y);

    glColor3ub(70,130,5);
    glVertex2i(x+50,y-50);

    glColor3ub(70,130,5);
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

void Background::Run(Weapon &gun1, Weapon &gun2)
{
    checkcollision(gun1,gun2);
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
    for (int i=nCube-1;i>=0;i--)
    {
        if (CubePtr[i].state==1)
        {
            CubePtr[i].draw();
        }
    }
}

void Background::checkcollision(Weapon &gun1,Weapon &gun2)
{
    for (int i=0;i<nCube;i++)
    {
        // weapon1
        if (gun1.GetBullet()->x()>CubePtr[i].GetX()
            && gun1.GetBullet()->x()< CubePtr[i].GetX()+50
            && gun1.GetBullet()->y()<CubePtr[i].GetY()
            && gun1.GetBullet()->y()>CubePtr[i].GetY()-50
            && CubePtr[i].state==1
            && gun1.GetBullet()->GetLife()>0
            )
        {
            CubePtr[i].state=0;
            gun1.GetBullet()->ChangeLife();
        }
        // weapon2
        if (gun2.GetBullet()->x()>CubePtr[i].GetX()
            && gun2.GetBullet()->x()< CubePtr[i].GetX()+50
            && gun2.GetBullet()->y()<CubePtr[i].GetY()
            && gun2.GetBullet()->y()>CubePtr[i].GetY()-50
            && CubePtr[i].state==1
            && gun2.GetBullet()->GetLife()>0
            )
        {
            CubePtr[i].state=0;
            gun2.GetBullet()->ChangeLife();
            
        }
    }
}


