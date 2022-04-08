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
//Вся игра
txCreateWindow (1200, 600);

txDisableAutoPause();
txTextCursor(false);

Personage dino = {100, 400, txLoadImage ("Картинки/DINOZAVR/DINOZAVR.bmp")};

Personage spike[50];
spike[0].pic = txLoadImage ("Картинки/SPIKE/SPIKE1.bmp");
for(int i=0; i<5; i++)
{
    spike[i] = {700+(i*300), 400, spike[0].pic, 10};
}

HDC GAME OVER = txLoadImage ("Картинки/ANIME/GAME OVER.bmp");
HDC DESERT = txLoadImage ("Картинки/FON/DESERT.bmp");

int score=0;
char score_list[100];

txSetColor (TX_BLACK, 5);
txSetFillColor (TX_WHITE);

  string PAGE = "Меню";

    while(true)
    {
     txClear();

        if(PAGE=="Меню")
        {
            txBegin();
            txSetColor(TX_WHITE);
            txSetFillColor(TX_BLACK);

            txRectangle (500,300,700,350);
            txDrawText(500,300,700,350,"START");

            if( txMouseX() >=500 &&
                txMouseY() >=300 &&
                txMouseX() <=700 &&
                txMouseY() <=350 &&
                txMouseButtons() == 1)
            {
                PAGE="Игра";
            }


            txRectangle (500,400,700,450);
            txDrawText(500,400,700,450,"HELP");

            if( txMouseX() >=500 &&
                txMouseY() >=400 &&
                txMouseX() <=700 &&
                txMouseY() <=450 &&
                txMouseButtons() == 1)
            {
                PAGE="HELP";
            }

            txRectangle (500,500,700,550);
            txDrawText(500,500,700,550,"EXIT");

            if( txMouseX() >=500 &&
                txMouseY() >=500 &&
                txMouseX() <=700 &&
                txMouseY() <=550 &&
                txMouseButtons() == 1)
            {
                return 0;
            }

            txEnd();

        }
         if(PAGE=="HELP")
         {

            txBegin();
             if (GetAsyncKeyState (VK_ESCAPE))
               {
                    PAGE="Меню";
               }

            txDrawText (0,0,1200,600,   "Управление:"
                                        "\n"
                                       "Пробел-Прыгать."
                                       "\n"
                                        "\n"
                                       "Описание Игры:"
                                       "\n"
                                       "\n"
                                       "У игры нет описания и цели,"
                                        "\n"
                                       "пока (и скорее это  всего на всегда недоделаный кусок кода)"
                                        "\n"
                                         "\n"
                                       " ВЕСЕЛИТЕСЬ С ТАКИМИ БАГАМИ."
                                       "\n");
            txEnd();
         }

         if(PAGE=="Игра")
         {
         txBegin();

           if (GetAsyncKeyState (VK_ESCAPE))
           {
                PAGE="Меню";
           }




        txBitBlt(txDC(),0, 0, 1300, 600, DESERT);

        txLine(0, 525, 1300, 525);

        //Динозавр
        Win32::TransparentBlt (txDC(), dino.x, dino.y, 100, 125, dino.pic, 0, 0, 200, 253, TX_WHITE);

        if(GetAsyncKeyState(VK_SPACE))
        {
         while(GetAsyncKeyState(VK_SPACE) == 1)
            txSleep(20);
         dino.v = - 30;
        }
        //Гравитация
        dino.y=dino.y+dino.v;
        dino.v = dino.v + 5;
        //Уровень земли
        if(dino.y>400)
        dino.y=400;

        if(dino.y<0)
        dino.y=0;

        //Кактус
        for(int i=0; i<5; i++)
        {
            drawSpike(spike[i]);
            spike[i].x = spike[i].x - spike[i].v;
        }


        //Столкновение


        for(int i=0; i<5; i++)
        {
            if(dino.x >= spike[i].x && dino.x+100 <= spike[i].x+100
                && dino.y <= spike[i].y && dino.y+125 >= spike[i].y+120)
            {
                txSetColor(TX_RED, 3);
                txSelectFont("Comic Sans", 50);
                txTextOut(400, 50, "GAME OVER");

                txSleep(5000);
                PAGE = "Меню";

            }
        }

//Очки


        sprintf(score_list, "Счёт %d", score);
        txTextOut (1200, 0, score_list);
        sprintf(score_list, "V= %d", dino.v);
        txTextOut (1200, 20, score_list);


        txSleep(10);
        txEnd();
        }
    }

    txDeleteDC (dino.pic);
    for(int i=0; i<3; i++)
    {
        txDeleteDC (spike[i].pic);
    }
    txDeleteDC (DESERT);
    txDeleteDC (GAME OVER);

return 0;
}


