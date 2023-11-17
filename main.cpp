#include "TXLib.h"
#include "button.cpp"
#include "picture.cpp"
#include <fstream>
#include <stdio.h>
#include <dirent.h>

using namespace std;

int get_w(string adress)
{
    FILE *f1 = fopen(adress.c_str(), "rb");
    unsigned char headerinfo[54];
    fread(headerinfo, sizeof(unsigned char), 54, f1);
    int w = *(int *)&headerinfo[18];

    return w;
}

int get_h(string adress)
{
    FILE *f1 = fopen(adress.c_str(), "rb");
    unsigned char headerinfo[54];
    fread(headerinfo, sizeof(unsigned char), 54, f1);
    int h = *(int *)&headerinfo[22];

    return h;
}

int readFromDir(string adress, Picture menuPic[], int count_pic)
{
    DIR *dir;
    struct dirent *ent;
    int X = 20;
    int Y = 100;
    if ((dir = opendir (adress.c_str())) != NULL)
    {
      while ((ent = readdir (dir)) != NULL)
      {
        if((string)ent->d_name != "." && (string)ent->d_name != "..")
        {
            if(Y<=800 && X == 20)
            {
                X = 20;
            }
            else if (Y>800)
            {
                X = 150;
                Y = 100;
            }
            menuPic[count_pic].x = X;
            menuPic[count_pic].y = Y;
            menuPic[count_pic].adress = adress + (string)ent->d_name;
            count_pic++;
            Y += 150;
        }
      }
      closedir (dir);
    }

    return count_pic;
}



int main()
{
    txCreateWindow (1250, 940);
    //инициализация кнопок
    int count_btn=6;
    int count_pic=0;
    char str[100];

    HDC Fon = txLoadImage("Pictures/Fon.bmp");

    Button btn[count_btn];
    btn[0] = {50, "build", "build"};
    btn[1] = {250, "defense", "defense"};
    btn[2] = {450, "resurces", "resurces"};
    btn[3] = {650, "other", "other"};
    btn[4] = {850, "trap", "trap"};
    btn[5] = {1050, "heroes", "heroes"};

    Picture menuPic[100];

    count_pic = readFromDir("pictures/build/", menuPic, count_pic);
    count_pic = readFromDir("pictures/defense/", menuPic, count_pic);
    count_pic = readFromDir("pictures/resurces/", menuPic, count_pic);
    count_pic = readFromDir("pictures/other/", menuPic, count_pic);
    count_pic = readFromDir("pictures/trap/", menuPic, count_pic);
    count_pic = readFromDir("pictures/heroes/", menuPic, count_pic);

    for(int i=0; i<count_pic; i++)
    {
        menuPic[i].pic = txLoadImage(menuPic[i].adress.c_str());

        menuPic[i].w = get_w(menuPic[i].adress);
        menuPic[i].h = get_h(menuPic[i].adress);

        menuPic[i].w_scr = menuPic[i].w/1.5;
        menuPic[i].h_scr = menuPic[i].h/1.5;

        menuPic[i].visible = false;

        string str = menuPic[i].adress;
        int pos1 = str.find("/");
        int pos2 = str.find("/", pos1+1);
        menuPic[i].category = str.substr(pos1+1, pos2-pos1-1);
    }

    Picture centrPic[100];

    int vybor = -1;
    bool mouse_click = false;
    int nCentrPic = 0;
    int npic = 0;

    while(!GetAsyncKeyState (VK_ESCAPE))
    {
        txBegin();
        //txSetFillColor(TX_GREEN);
        txClear();
        Fon = txLoadImage ("pictures/Fon.bmp");
        txTransparentBlt (txDC(), 0, 0, 1250, 940, Fon);

        for(int i=0; i<count_btn; i++)
        {
            btn[i].Draw();
        }

        for(int i=0; i<count_pic; i++)
        {
            menuPic[i].Draw();
        }

        for(int i=0; i<nCentrPic; i++)
        {
            centrPic[i].Draw();
        }

       for(int ib=0; ib<count_btn; ib++)
        {
            if(btn[ib].Click())
            {
                for(int ip=0; ip<count_pic; ip++)
                {
                    menuPic[ip].visible = false;
                    if(menuPic[ip].category == btn[ib].category)
                    {
                        menuPic[ip].visible = true;
                    }
                }
            }
        }

        for(int npic=0; npic<count_pic; npic++)
        {
            if(menuPic[npic].Click() && menuPic[npic].visible)
            {
                while(txMouseButtons() == 1)
                {
                    txSleep(10);
                }
                centrPic[nCentrPic]  = {500,
                                        100,
                                        menuPic[npic].adress,
                                        menuPic[npic].pic,
                                        menuPic[npic].w,
                                        menuPic[npic].h,
                                        menuPic[npic].w,
                                        menuPic[npic].h,
                                        menuPic[npic].visible,
                                        menuPic[npic].category};

                nCentrPic ++;
            }
        }


        for(int i=0; i<nCentrPic; i++)
        {
            if(centrPic[i].Click() && centrPic[i].visible)
            {
                vybor = i;
                mouse_click = false;
            }
        }

        if(vybor>=0 && GetAsyncKeyState (VK_DELETE))
        {
            centrPic[vybor] = centrPic[nCentrPic-1];
            nCentrPic--;
            vybor = -1;
            mouse_click = true;
        }


        /*char str[10];
        sprintf(str, "индекс чёто там  = %d", vybor);
        txTextOut(50, 650, str);*/


        if(vybor>=0)
        {
            if (GetAsyncKeyState (VK_LEFT))
            {
                centrPic[vybor].x -= 5;
            }

            if (GetAsyncKeyState (VK_RIGHT))
            {
                centrPic[vybor].x += 5;
            }

            if (GetAsyncKeyState (VK_UP))
                {
                centrPic[vybor].y -= 5;
            }

            if (GetAsyncKeyState (VK_DOWN))
            {
                centrPic[vybor].y += 5;
            }

            if (GetAsyncKeyState (VK_OEM_PLUS) || GetAsyncKeyState(VK_ADD))
            {
                centrPic[vybor].w_scr = centrPic[vybor].w_scr * 1.1;
                centrPic[vybor].h_scr = centrPic[vybor].h_scr * 1.1;
            }

            if (GetAsyncKeyState (VK_OEM_MINUS) || GetAsyncKeyState(VK_SUBTRACT))
            {
                centrPic[vybor].w_scr = centrPic[vybor].w_scr * 0.9;
                centrPic[vybor].h_scr = centrPic[vybor].h_scr * 0.9;
            }
        }

        if(vybor>=0)
        {
            if(txMouseButtons() == 1 && !mouse_click)
            {
                centrPic[vybor].x = txMouseX() - centrPic[vybor].w_scr/2;
                centrPic[vybor].y = txMouseY() - centrPic[vybor].h_scr/2;
            }
            else
            {
                if(txMouseButtons() !=1)
                {
                    mouse_click = true;
                }
            }
        }

        txSleep(10);
        txEnd();
        }

    for(int i=0; i<count_pic; i++)
    {
        txDeleteDC (menuPic[i].pic);
    }

    for(int i=0; i<nCentrPic; i++)
    {
        txDeleteDC (centrPic[i].pic);
    }


return 0;
}
