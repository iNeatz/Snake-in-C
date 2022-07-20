#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define N 20
#define M 40

int i,j, Field[N][M], x, y, Gy, Head, Tail, Game, Frogs, a,b, var, dir, score, HighScore, Speed;

FILE *f;

void hideCursor()
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void snakeInit()
{
    f = fopen("highscore.txt", "r");
    fscanf(f,"%d",&HighScore);
    fclose(f);

    for(i=0; i<N; i++)
    {
        for(j=0;j<M;j++)
        {
            Field[i][j] = 0;
        }
    }

    x=N/2;
    y=M/2;
    Gy=y;
    Head=5;
    Tail=1;
    Game=0;
    Frogs=0;
    dir='d';
    score=0;
    Speed=99;

    for(i=0;i<Head;i++)
    {
        Gy++;
        Field[x][Gy-Head] = i+1;
    }
}

void print()
{
//BORDER of the GAME
    //TOP ROW BORDER
    for(i=0; i<=M+1; i++){
        if(i==0)
            printf("%c",201);
        else if(i==M+1)
            printf("%c",187);
        else
            printf("%c",205);
    }

    printf("\n");

    //SIDE BORDERS
    for(i=0;i<N;i++){
        printf("%c", 186);

        for(j=0; j<M; j++){
            if(Field[i][j]==0)
                printf(" ");
            if(Field[i][j]>0 && Field[i][j] != Head)
                printf("%c",176);
            if(Field[i][j] == Head)
                printf("%c",178);
            if(Field[i][j] == -1)
                printf("%c",14);
            if(j==M-1)
                printf("%c\n", 186);
        }
    }

    //BOTTOM ROW BORDER
    for(i=0; i<=M+1; i++){
        if(i==0)
            printf("%c",200);
        else if(i==M+1)
            printf("%c",188);
        else
            printf("%c",205);
    }

    printf("\nCURRENT SCORE: %d", score);
    printf("\nHIGH SCORE: %d", HighScore);
}

void ResetScreenPosition()
{
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

void Random()
{
    srand(time(0));
    a = 1 + rand()%(N-2);
    b = 1 + rand()%(M-2);

    if(Frogs == 0 && Field[a][b] == 0)
    {
        Field[a][b] = -1;
        Frogs = 1;

        if(Speed>10 && score!=0)
            Speed-=5;
    }
}

int getch_noblock()
{
    if(_kbhit())
        return _getch();
    else
        return -1;
}

void movement()
{
    var = getch_noblock();
    var = tolower(var);

    if(((var=='d' || var=='a') || (var=='w' || var=='s')) && abs(dir - var)>5)
        dir = var;
    if(dir == 'd')
    {
        y++;
        if(y==M)
            y=0;
        if(Field[x][y]!=0 && Field[x][y]!=-1)
            Gameover();
        if(Field[x][y]==-1)
        {
            Tail-=2;
            score+=5;
            Frogs = 0;
        }
        Head++;
        Field[x][y] = Head;
    }
    if(dir == 's')
    {
        x++;
        if(x==N)
            x=0;
        if(Field[x][y]!=0 && Field[x][y]!=-1)
            Gameover();
        if(Field[x][y]==-1)
        {
            Tail-=2;
            score+=5;
            Frogs = 0;
        }
        Head++;
        Field[x][y] = Head;
    }
    if(dir == 'w')
    {
        x--;
        if(x==0)
            x=N-1;
        if(Field[x][y]!=0 && Field[x][y]!=-1)
            Gameover();
        if(Field[x][y]==-1)
        {
            Tail-=2;
            score+=5;
            Frogs = 0;
        }
        Head++;
        Field[x][y] = Head;
    }
    if(dir == 'a')
    {
        y--;
        if(y==0)
            y=M-1;
        if(Field[x][y]!=0 && Field[x][y]!=-1)
            Gameover();
        if(Field[x][y]==-1)
        {
            Tail-=2;
            score+=5;
            Frogs = 0;
        }
        Head++;
        Field[x][y] = Head;
    }
}

void TailRemove()
{
    for(i=0; i<N; i++)
    {
        for(j=0;j<M;j++)
        {
            if(Field[i][j]==Tail)
                Field[i][j] = 0;
        }
    }
    Tail++;
}

void Gameover()
{
    printf("\a");
    Sleep(1500);
    system("cls");

    if(score>HighScore)
    {
        printf("\n\n     NEW HIGHSCORE: %d !!!!!!!! \n", score);
        system("pause");
        f=fopen("highscore.txt", "w");
        fprintf(f,"%d",score);
        fclose(f);
    }
    system("cls");
    printf("\n\n         GAME OVER !!!!!!!! \n\n");
    printf("         Score: %d !!!!!!!! \n\n", score);
    printf("\n  Press ENTER key to Play Again...\n");
    printf("  OR Press ESC key to Exit...\n\n");

    while(1)
    {
        var = getch_noblock();
        if(var==13)
        {
            Game = 0;
            snakeInit();
            break;
        }
        else if(var==27)
        {
            Game = 1;
            break;
        }
    }
    system("cls");
}

void main()
{
    hideCursor();
    snakeInit();
    //Print the borders of the game

    while(Game==0)
    {
        print();
        ResetScreenPosition();
        Random();
        movement();
        TailRemove();
        Sleep(Speed);
    }


}
