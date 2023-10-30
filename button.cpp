#include "TXLib.h"
struct Button
{
    int x;
    const char* name;
    string category;

    void Draw()
    {
        txSetColor(TX_TRANSPARENT);
        txSetFillColor(TX_GREY);
        Win32::RoundRect (txDC(), x+5, 35, x+155, 75, 30, 30);
        txSetColor(TX_BLACK, 3);
        txSetFillColor(TX_WHITE);
        Win32::RoundRect (txDC(), x, 30, x+150, 70, 30, 30);
        txSetColor(TX_BLACK);
        txSelectFont("Arial", 24);
        txDrawText(x, 30, x+150, 70, name);
    }

    bool Click()
    {
        return(txMouseButtons() == 1 &&
        txMouseX()>= x && txMouseX()<=x+150 &&
        txMouseY()>= 35 && txMouseY()<=75);
    }
};
