#include "TXLib.h"

struct Personage
{
    int x;
    int y;
    HDC pic;
    int v;
};

void drawSpike(Personage spike)
{
    Win32::TransparentBlt (txDC(), spike.x, spike.y, 100, 120, spike.pic, 0, 0, 200, 243, TX_WHITE);
}

int main()
{
txCreateWindow (1300, 600);

txDisableAutoPause();
txTextCursor(false);

Personage dino = {100, 400, txLoadImage ("????????/DINOZAVR/DINOZAVR.bmp")};

Personage spike[50];
spike[0].pic = txLoadImage ("????????/SPIKE/SPIKE1.bmp");
for(int i=0; i<3; i++)
{
    spike[i] = {700+(i*300), 400, spike[0].pic, 10};
}

//HDC REI = txLoadImage ("????????/ANIME/REI.bmp");
HDC DESERT = txLoadImage ("????????/FON/DESERT.bmp");

int score=0;
char score_list[100];

txSetColor (TX_BLACK, 5);
txSetFillColor (TX_WHITE);


    while(!GetAsyncKeyState (VK_ESCAPE))
    {
        txClear();
        txBegin();

        txBitBlt(txDC(),0, 0, 1300, 600, DESERT);

        txLine(0, 525, 1300, 525);

        //????????
        Win32::TransparentBlt (txDC(), dino.x, dino.y, 100, 125, dino.pic, 0, 0, 200, 253, TX_WHITE);

        if(GetAsyncKeyState(VK_SPACE))
        {
         while(GetAsyncKeyState(VK_SPACE) == 1)
            txSleep(20);
         dino.v = - 30;
        }
        //??????????
        dino.y=dino.y+dino.v;
        dino.v = dino.v + 5;
        //??????? ?????
        if(dino.y>400)
        dino.y=400;

        if(dino.y<0)
        dino.y=0;

        //??????
        for(int i=0; i<3; i++)
        {
            drawSpike(spike[i]);
            spike[i].x = spike[i].x - spike[i].v;
        }

        //????

        if(dino.v > 50 && dino.y == 400)
        {
            score++;
        }




        sprintf(score_list, "???? %d", score);
        txTextOut (1200, 0, score_list);
        sprintf(score_list, "V= %d", dino.v);
        txTextOut (1200, 20, score_list);


        txSleep(10);
        txEnd();
    }

    txDeleteDC (dino.pic);
    for(int i=0; i<3; i++)
    {
        txDeleteDC (spike[i].pic);
    }
    txDeleteDC (DESERT);

return 0;
}


