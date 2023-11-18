#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <assert.h>

#define width 65
#define height 25
#define Rspeed 2
#define c_border '#'
#define c_racket '@'
#define c_brick (char)176
#define brickWidth 3

typedef struct
{
    int x, y;
    int w;
} TRacket;

typedef struct
{
    float x, y;
    int ix, iy;
    float alpha;
    float speed;
} TBall;

char lvlMap[height][width];
char mas[height][width + 1];
TRacket racket;
TBall ball;
int hitCnt = 0;
int maxHitCnt = 0;
int lvl = 1;
BOOL run = FALSE;

void moveball(float x, float y)
{
    ball.x = x;
    ball.y = y;
    ball.ix = (int)round(ball.x);
    ball.iy = (int)round(ball.y);
}

void initball()
{
    moveball(2, 2);
    ball.alpha = -1;
    ball.speed = 1;
}

void AutoMoveBall()
{
    if (ball.alpha < 0) ball.alpha += M_PI * 2;
    if (ball.alpha > M_PI * 2) ball.alpha -= M_PI * 2;

    TBall bl = ball;
    moveball(ball.x + cos(ball.alpha) * ball.speed, ball.y + sin(ball.alpha) * ball.speed);
    if ((mas[ball.iy][ball.ix] ==  c_border) ||
        (mas[ball.iy][ball.ix] ==  c_brick) ||
        (mas[ball.iy][ball.ix] ==  c_racket))
    {

        if (mas[ball.iy][ball.ix] == c_brick)
        {
            int brickNom = (ball.ix - 1) / brickWidth;
            int dx = 1 + brickNom * brickWidth;
            for (int i = 0; i < brickWidth; i++)
            {
                static char *c;
                c = &lvlMap[ball.iy][i + dx];
                if (*c == c_brick) *c = ' ';
            }
        }
        if (mas[ball.iy][ball.ix] ==  c_racket)
        {
            hitCnt++;
            float pos = ball.x - racket.x;
            float psi = pos / racket.w * 2;
            psi = (psi - 1) * M_PI_2 * 0.9;
            assert(psi < M_PI_2 && psi > -M_PI_2);
            bl.alpha = -M_PI_2 + psi;
        }
        else if ((ball.ix != bl.ix) && (ball.iy != bl.iy))
        {
            if (mas[bl.iy][ball.ix] == mas[ball.iy][bl.ix])
            {
                bl.alpha = bl.alpha + M_PI;
            }
            else
            {
                if (mas[bl.iy][ball.ix] == c_border)
                {
                    bl.alpha = (2 * M_PI - bl.alpha) + M_PI;
                }
                else
                {
            bl.alpha = (2 * M_PI - bl.alpha);
                }
            }
        }
        else if (ball.iy == bl.iy)
        {
            bl.alpha = (2 * M_PI - bl.alpha) + M_PI;
        }
        else
        {
            bl.alpha = (2 * M_PI - bl.alpha);
        }

        ball = bl;
        AutoMoveBall;
    }

}

void putball()
{
    mas[ball.iy][ball.ix] = '*';
}

void initRacket()
{
    racket.w = 7;
    racket.x = (width - racket.w) / 2;
    racket.y = height - 1;
}



void PutRacket()
{
    for (int i = racket.x; i < racket.x + racket.w; i++)
    {
        mas[racket.y][i] = c_racket;
    }
}

void lvlMapPuzzile(int lvl)
{
    switch(lvl)
    {
        case 1:
            for (int i = 7; i < width - 7; i++)
            {
                lvlMap[5][i] = lvlMap[6][i] = c_brick;
            }
            break;

        case 2:
                for (int i = 19; i <= 48; i++)
                {
                    lvlMap[1][i] = lvlMap[2][i] = c_brick;
                    lvlMap[8][i] = lvlMap[9][i] = c_brick;
                    lvlMap[10][i] = c_border;
                }
            break;

        case 3:
            for (int j = 1; j < 10; j++)
                for (int i = 1; i < 62; i += 6)
                    lvlMap[j][i] = lvlMap[j][i + 1] = lvlMap[j][i + 2] = c_brick;
            break;
    }
}

void setcur(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void lvlMapInit(int lvl)
{
    memset(lvlMap, ' ', sizeof(lvlMap));

    lvlMapPuzzile(lvl);

    for (int i = 0; i < width; i++)
    {
        lvlMap[0][i] = c_border;
    }
    for (int j = 0; j < height; j++)
    {
        lvlMap[j][0] = lvlMap[j][width - 1] = c_border;
    }
}

void lvlMapPut()
{
    memset(mas, 0, sizeof(mas));

    for (int j = 0; j < height; j++)
    {
        memcpy(mas[j], lvlMap[j], sizeof(**lvlMap) * width);
    }
}

void show()
{
    setcur(0, 0);
    for (int i = 0; i < height; i++)
    {
        printf("%s", mas[i]);
        if (i == 1)
        {
            printf("   lvl %i   ", lvl);
        }
        if (i == 3)
        {
            printf("   hit %i   ", hitCnt);
        }
        if (i == 4)
        {
            printf("   max %i   ", maxHitCnt);
        }
        if (i < height - 1)
        {
            printf("\n");
        }
    }

}

void ShowPreview()
{
    system("cls");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n \t\t\t\t                     LEVEL %d", lvl);
    Sleep(3000);
    system("cls");
}

void moveRacket(int x)
{
    racket.x = x;
    if (racket.x < 1)
    {
        racket.x = 1;
    }
    if (racket.x + racket.w >= width)
    {
        racket.x = width - 1 - racket.w;
    }
}

void checkFaild()
{
    if (ball.iy >= height - 1)
        {
            run = FALSE;
            if (hitCnt > maxHitCnt)
            {
                maxHitCnt = hitCnt;
            }
            hitCnt = 0;
        }
    }

int lvlMapBrickCount()
{
    int cnt = 0;
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i ++)
        {
            if (lvlMap[j][i] == c_brick)
                cnt++;
        }
    }
    return cnt;
}

void checkWin()
{
    if (lvlMapBrickCount() == 0)
        {
            if (lvl < 3)
            {
                lvl++;
                ShowPreview();
                lvlMapInit(lvl);
            }
            else
            {
                system("cls");
                printf("\n\n\n\n\n\n\n\n\n\n\n\n \t\t\t\t                     GAME END YOU WON ");
                Sleep(3000);
                exit(0);
            }

            run = FALSE;
            maxHitCnt = 0;
            hitCnt = 0;
        }
}

void BallWork()
{
    if (run)
        {
            AutoMoveBall();
        }
        else
        {
            moveball(racket.x + racket.w / 2, racket.y - 1);
        }
}

int main()
{
    initRacket();
    initball();
    lvlMapInit(lvl);
    ShowPreview();
    do
    {

        BallWork();

        checkFaild();

        lvlMapBrickCount();

        checkWin();

        lvlMapPut();
        PutRacket();
        putball();
        show();

        if (GetKeyState('A') < 0) moveRacket(racket.x - Rspeed);
        if (GetKeyState('D') < 0) moveRacket(racket.x + Rspeed);
        if (GetKeyState('W') < 0) run = TRUE;

        Sleep(10);

    } while(GetKeyState(VK_ESCAPE) >= 0);
    return 0;
}
