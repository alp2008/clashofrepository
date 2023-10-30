#include "TXLib.h"
#include "button.cpp"
#include "picture.cpp"

int main()
{
    txCreateWindow (1200, 700);
    //инициализация кнопок
    int count_btn=3;
    int count_pic=8;
    Button btn[count_btn];
    btn[0] = {50, "обычные здания", "обычные здания"};
    btn[1] = {250, "защитные здания", "защитные здания"};
    btn[2] = {450, "ресурсы", "ресурсы"};

    Picture menuPic[count_pic];
    menuPic[0] = {20, 100, "pictures/build/ratusha.bmp",    txLoadImage ("pictures/build/ratusha.bmp"), 120, 120, 225, 225};
    menuPic[1] = {20, 300, "pictures/build/bilder.bmp",     txLoadImage ("pictures/build/bilder.bmp"),  54,  63,  54,  63 };
    menuPic[2] = {20, 100, "pictures/defense/zabor.bmp",    txLoadImage ("pictures/defense/zabor.bmp"), 120, 120, 238, 212};
    menuPic[3] = {20, 300, "pictures/defense/ad.bmp",       txLoadImage ("pictures/defense/ad.bmp"),    120, 120, 155, 215};
    menuPic[4] = {20, 500, "pictures/defense/dolbit.bmp",   txLoadImage ("pictures/defense/dolbit.bmp"),120, 120, 159, 190};
    menuPic[5] = {120,100, "pictures/defense/gun2.bmp",     txLoadImage ("pictures/defense/gun2.bmp"),  120, 120, 82,  78 };
    menuPic[6] = {120,300, "pictures/defense/negr.bmp",     txLoadImage ("pictures/defense/negr.bmp"),  120, 120, 760, 760};
    menuPic[7] = {120,500, "pictures/defense/tesla.bmp",    txLoadImage ("pictures/defense/tesla.bmp"), 120, 120, 170, 192};

    for(int i=0; i<count_pic; i++)
    {
        menuPic[i].visible = false;

        string str = menuPic[i].adress.c_str();
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
        sprintf(str, "индекс чёто там  = %d", vybor);
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
