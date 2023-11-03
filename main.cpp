#include "TXLib.h"
#include "button.cpp"
#include "picture.cpp"
#include <fstream>

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

int main()
{
    txCreateWindow (1200, 700);
    //������������� ������
    int count_btn=3;
    int count_pic=8;

    Button btn[count_btn];
    btn[0] = {50, "������� ������", "build"};
    btn[1] = {250, "�������� ������", "defense"};
    btn[2] = {450, "�������", "resurse"};

    Picture menuPic[count_pic];
    menuPic[0] = {20, 100, "pictures/build/ratusha.bmp"};
    menuPic[1] = {20, 300, "pictures/build/bilder.bmp"};
    menuPic[2] = {20, 100, "pictures/defense/zabor.bmp"};
    menuPic[3] = {20, 300, "pictures/defense/ad.bmp"};
    menuPic[4] = {20, 500, "pictures/defense/dolbit.bmp"};
    menuPic[5] = {120,100, "pictures/defense/gun2.bmp"};
    menuPic[6] = {120,300, "pictures/defense/negr.bmp"};
    menuPic[7] = {120,500, "pictures/defense/tesla.bmp"};

    for(int i=0; i<count_pic; i++)
    {
        menuPic[i].pic = txLoadImage(menuPic[i].adress.c_str());

        menuPic[i].w = get_w(menuPic[i].adress);
        menuPic[i].h = get_h(menuPic[i].adress);

        menuPic[i].w_scr = menuPic[i].w/3;
        menuPic[i].h_scr = menuPic[i].h/3;

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
        txSetColor(TX_GREEN);
        txSetFillColor(TX_GREEN);
        txClear();

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


        char str[10];
        sprintf(str, "������ ���� ���  = %d", vybor);
        txTextOut(50, 650, str);


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

        txSleep(50);
        txEnd();
        }

    for (int i=0; i<count_pic; i++)
    {
        txDeleteDC(menuPic[i].pic);
    }
    for (int i=0; i<count_pic; i++)
    {
        txDeleteDC(centrPic[i].pic);
    }

txDisableAutoPause();
txTextCursor (false);
return 0;
}
